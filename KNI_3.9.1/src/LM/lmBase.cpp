/*
 *   Katana Native Interface - A C++ interface to the robot arm Katana.
 *   Copyright (C) 2005 Neuronics AG
 *   Check out the AUTHORS file for detailed contact information.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include "../../include/KNI_LM/lmBase.h"

#include "common/Timer.h"
#include <cmath>
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <iostream>

/// Polling position every POLLFREQUENCY milliseconds
const int POLLFREQUENCY = 300;

void CLMBase::fillPoints(double vmax) {

	double acc = 1500;	// currently fixed
	double dec = 1500;	// currently fixed

	trajectory.distance =
	    (int) pow(pow((trajectory.arr_actpos[0]
	                   - trajectory.arr_tarpos[0]),2)
	              + pow((trajectory.arr_actpos[1]
	                     - trajectory.arr_tarpos[1]),2)
	              + pow((trajectory.arr_actpos[2]
	                     - trajectory.arr_tarpos[2]),2),
	              0.5);

	// minimun distance in order to reach vmax
	double dgrez = (pow(vmax,2)/2) * ((1/acc)+(1/dec));
	// if distance < dgrez -> vmax is never reached

	for (int i=0; i<trajectory.number_of_points; i++) {

		//------------------------------------------------------------------//
		// Fill trajectory.points with the relative positition and absolute
		// time at each point to be interpolated

		if (trajectory.distance > dgrez) { //vmax will be reached

			trajectory.time =
			    (trajectory.distance/vmax)
			    + ((vmax/2)*((1/acc)+(1/dec)));
			trajectory.points[i].time =
			    ((double)i/(trajectory.number_of_points-1))
			    * trajectory.time;

			// acceleration phase
			if (trajectory.points[i].time < (vmax/acc)) {
				trajectory.points[i].pos =
				    (acc / 2)
				    * pow(trajectory.points[i].time,2);
			} else {
				if (trajectory.points[i].time
				        < (trajectory.time - (vmax/dec))) {	// maximum speed
					trajectory.points[i].pos =
					    vmax
					    * (trajectory.points[i].time
					       - ((1/2)
					          * vmax/acc));
				} else { // deceleration phase
					trajectory.points[i].pos =
					    trajectory.distance
					    - (dec*((pow(trajectory.points[i].time,2)/2)
					            -(trajectory.time*trajectory.points[i].time)
					            +(pow(trajectory.time,2)/2)));
				}
			}

		} else { // vmax will not be reached

			trajectory.time = (8 * trajectory.distance) / pow((acc + dec),
			                  (1/2));
			trajectory.points[i].time =
			    ((double)i/trajectory.number_of_points)
			    * trajectory.time;
			if (trajectory.points[i].time < (trajectory.time/2)) {
				trajectory.points[i].pos =
				    (acc/2)
				    * pow(trajectory.points[i].time,2);
			} else {
				trajectory.points[i].pos =
				    trajectory.distance
				    - (dec*((pow(trajectory.points[i].time,2)/2)
				            -(trajectory.time*trajectory.points[i].time)
				            +(pow(trajectory.time,2)/2)));
			}

		}

		//------------------------------------------------------------------//
		// Fill trajectory.dt, it will be used in the following calculations
		trajectory.dt =
		    trajectory.time / (trajectory.number_of_points - 1);
		//------------------------------------------------------------------//
		// Fill trajectory.motors with the position of the motors at each
		// point to be interpolated

		double Xm = trajectory.arr_actpos[0]
		            + ((trajectory.points[i].pos/trajectory.distance)
		               * (trajectory.arr_tarpos[0] - trajectory.arr_actpos[0]));
		double Ym = trajectory.arr_actpos[1]
		            + ((trajectory.points[i].pos/trajectory.distance)
		               * (trajectory.arr_tarpos[1] - trajectory.arr_actpos[1]));
		double Zm = trajectory.arr_actpos[2]
		            + ((trajectory.points[i].pos/trajectory.distance)
		               * (trajectory.arr_tarpos[2] - trajectory.arr_actpos[2]));
		double Alm = trajectory.arr_actpos[3]
		             + ((trajectory.points[i].pos/trajectory.distance)
		                * (trajectory.arr_tarpos[3] - trajectory.arr_actpos[3]));
		double Bem = trajectory.arr_actpos[4]
		             + ((trajectory.points[i].pos/trajectory.distance)
		                * (trajectory.arr_tarpos[4] - trajectory.arr_actpos[4]));
		double Gam = trajectory.arr_actpos[5]
		             + ((trajectory.points[i].pos/trajectory.distance)
		                * (trajectory.arr_tarpos[5] - trajectory.arr_actpos[5]));

		std::vector<int> solution(getNumberOfMotors());
		std::vector<int> referenceEncoders(getNumberOfMotors());
		if(i==0) {
			for(int j = 0; j < getNumberOfMotors(); ++j) {
				referenceEncoders[j] = base->GetMOT()->arr[j].GetPVP()->pos;
			}
		} else {
			for(int j = 0; j < getNumberOfMotors(); ++j) {
				referenceEncoders[j] = trajectory.motors[j][i-1];
			}
		}

		IKCalculate(Xm, Ym, Zm, Alm, Bem, Gam, solution.begin(), referenceEncoders);

		for (int j=0; j < getNumberOfMotors(); j++)
			trajectory.motors[j][i] = solution[j];
	}
}


void CLMBase::polDeviratives() {

	// These calculations are fixed to 5 points and 5 motors,
	//should be extended to n elements...

	double e1,e2,e3;
	for (int mot=0; mot < getNumberOfMotors(); mot++) {

		e1 = (double)(3/trajectory.dt)
		     * (double)(trajectory.motors[mot][2] - trajectory.motors[mot][0]);
		e2 = (double)(3/trajectory.dt)
		     * (double)(trajectory.motors[mot][3]
		                - trajectory.motors[mot][1]);
		e3 = (double)(3/trajectory.dt)
		     * (double)(trajectory.motors[mot][4]
		                - trajectory.motors[mot][2]);

		trajectory.derivatives[mot][0] = 0;
		trajectory.derivatives[mot][1] = ((15*e1)-(4*e2)+e3)/56;
		trajectory.derivatives[mot][2] = (-e1+(4*e2)-e3)/14;
		trajectory.derivatives[mot][3] = (e1-(4*e2)+(15*e3))/56;
		trajectory.derivatives[mot][4] = 0;
	}
}


void CLMBase::polCoefficients() {

	for (int mot=0; mot < getNumberOfMotors(); mot++) {
		// currently fixed to 5 motors
		for (int pol=0; pol< trajectory.number_of_points - 1; pol++) {
			trajectory.coefficients[mot][pol][0] =
			    trajectory.motors[mot][1 + pol]
			    - trajectory.motors[mot][0 + pol];
			trajectory.coefficients[mot][pol][1] =
			    trajectory.coefficients[mot][pol][0]
			    - (trajectory.dt * trajectory.derivatives[mot][0 + pol]);
			trajectory.coefficients[mot][pol][2] =
			    (trajectory.dt * trajectory.derivatives[mot][1 + pol])
			    - trajectory.coefficients[mot][pol][0];
			trajectory.coefficients[mot][pol][3] =
			    trajectory.coefficients[mot][pol][2]
			    - trajectory.coefficients[mot][pol][1];
		}
	}
}


void CLMBase::calcParameters(double* arr_actpos,
                             double* arr_tarpos,
                             double vmax) {

	int shift3 = 32768;
	int shift2 = 1024;
	int shift1 = 64;
	//    int shift0 = 0;

	trajectory.arr_actpos = arr_actpos;
	trajectory.arr_tarpos = arr_tarpos;

	fillPoints(vmax);

	polDeviratives();
	polCoefficients();

	for (int mot=0; mot<getNumberOfMotors(); mot++) {
		for (int pol=0; pol< trajectory.number_of_points - 1; pol++) {

			// important: in K4D this is rounded instead of casted
			trajectory.parameters[mot][pol][3] =
			    (short)(pow(0.01,3)
			            * trajectory.coefficients[mot][pol][3]
			            / pow(trajectory.dt,3) * shift3);
			trajectory.parameters[mot][pol][2] =
			    (short)((pow(0.01,2)
			             * (trajectory.coefficients[mot][pol][1]
			                - trajectory.coefficients[mot][pol][3])
			             / pow(trajectory.dt,2)) * shift2);
			trajectory.parameters[mot][pol][1] =
			    (short)(((0.01
			              * (trajectory.coefficients[mot][pol][0]
			                 - trajectory.coefficients[mot][pol][1]))
			             /trajectory.dt) * shift1);
			trajectory.parameters[mot][pol][0] =
			    (short)(trajectory.motors[mot][pol]);
		}
	}
}

/****************************************************************************/
/****************************************************************************/

void CLMBase::initLM() {

	trajectory.number_of_points = 5;

	short number_of_coefficients = 4;
	short number_of_parameters = 4;

	trajectory.points = new TLM_points[trajectory.number_of_points];

	trajectory.motors = new short* [getNumberOfMotors()];
	for (int i=0; i<getNumberOfMotors(); i++)
		trajectory.motors[i] = new short[trajectory.number_of_points];

	trajectory.derivatives = new double* [getNumberOfMotors()];
	for (int i=0; i<getNumberOfMotors(); i++)
		trajectory.derivatives[i] = new double[trajectory.number_of_points];

	trajectory.coefficients = new double** [getNumberOfMotors()];
	for (int i=0; i<getNumberOfMotors(); i++)
		trajectory.coefficients[i] =
		    new double* [trajectory.number_of_points-1];
	for (int i=0; i<getNumberOfMotors(); i++)
		for (int j=0; j<trajectory.number_of_points-1; j++)
			trajectory.coefficients[i][j] =
			    new double[number_of_coefficients];

	trajectory.parameters = new short** [getNumberOfMotors()];
	for (int i=0; i<getNumberOfMotors(); i++)
		trajectory.parameters[i] =
		    new short* [trajectory.number_of_points-1];
	for (int i=0; i<getNumberOfMotors(); i++)
		for (int j=0; j<trajectory.number_of_points-1; j++)
			trajectory.parameters[i][j] =
			    new short[number_of_parameters];

	blendtrajectory.referencepoints = new TPoint6D[6];
	blendtrajectory.blendtrace = new TBlendtrace[4];
	blendtrajectory.splinepoints = new TSplinepoint[256]; // for prototype, should be handles differently

	_isInitialized = true;
}

// Linear movement with four splines
void CLMBase::movLM2PwithL(double X1, double Y1, double Z1, double Al1,
		double Be1, double Ga1, double X2, double Y2, double Z2, double Al2,
		double Be2, double Ga2, bool exactflag, double vmax, bool wait,
		int tolerance, long timeout) {

	// check if the robot buffer is ready to receive a new linear movement

	bool motors_ready = false;

	while (!motors_ready) {
		motors_ready = true;
		for (int idx = 0; idx < getNumberOfMotors() - 1; idx++) {
			base->GetMOT()->arr[idx].recvPVP();
			motors_ready &= (base->GetMOT()->arr[idx].GetPVP()->msf != 152);
		}
	}

	double arr_tarpos[6] = {X2, Y2, Z2, Al2, Be2, Ga2};
	// target position in cartesian units
	double arr_actpos[6] = {X1, Y1, Z1, Al1, Be1, Ga1};
	// source position in cartesian units

	calcParameters(arr_actpos, arr_tarpos, vmax);

	byte p[38];	//packet

	for (int mot = 0; mot < getNumberOfMotors()-1; ++mot) {
		// it is implemented only for 5 motors

		p[0] = 'L';
		p[1] = mot + 1;
		p[2] =
		    (byte)(trajectory.motors[mot][trajectory.number_of_points - 1]
		           >> 8);
		p[3] =
		    (byte)(trajectory.motors[mot][trajectory.number_of_points - 1]);
		p[4] = (byte)((int)((double)(trajectory.dt)/0.01) >> 8);
		p[5] = (byte)((int)((double)(trajectory.dt)/0.01));

		for (int pol=0; pol< trajectory.number_of_points - 1; pol++) {
			p[6 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][0]
			                        >> 8);
			p[7 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][0]);
			p[8 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][1]
			                        >> 8);
			p[9 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][1]);
			p[10 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][2]
			                         >> 8);
			p[11 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][2]);
			p[12 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][3]
			                         >> 8);
			p[13 + 8 * pol] = (byte)(trajectory.parameters[mot][pol][3]);
		}
		base->sendSLMP(p);
	}

	base->sendSLM(exactflag);

	if (!wait)
		return;

	bool pos_reached = true;
	KNI::Timer t(timeout), poll_t(POLLFREQUENCY);
	t.Start();
	while (true) {
		if (t.Elapsed())
			throw MotorTimeoutException();
		pos_reached = true;
		poll_t.Start();

		base->recvMPS();
		base->recvGMS();

		for (int idx=0; idx<5; idx++) {
			pos_reached &= (std::abs(trajectory.motors[idx][trajectory.number_of_points - 1] - base->GetMOT()->arr[idx].GetPVP()->pos) < tolerance);
			if (base->GetMOT()->arr[idx].GetPVP()->msf == 40)
				throw MotorCrashException();
		}
		if (pos_reached)
			break;

		poll_t.WaitUntilElapsed();
	}

}

void CLMBase::movLM2P4D(double X1, double Y1, double Z1,
                        double Al1, double Be1, double Ga1,
                        double X2, double Y2, double Z2,
                        double Al2, double Be2, double Ga2,
                        bool exactflag, double vmax, bool wait, int tolerance, long timeout) {

	// check if the robot buffer is ready to receive a new linear movement

	bool motors_ready = false;

	while (!motors_ready) {
		motors_ready = true;
		for (int idx = 0; idx < getNumberOfMotors() - 1; idx++) {
			base->GetMOT()->arr[idx].recvPVP();
			motors_ready &= (base->GetMOT()->arr[idx].GetPVP()->msf != 152);
		}
	}

	double arr_tarpos[6] = {X2, Y2, Z2, Al2, Be2, Ga2};
	// target position in cartesian units
	double arr_actpos[6] = {X1, Y1, Z1, Al1, Be1, Ga1};
	// source position in cartesian units

	calcParameters(arr_actpos, arr_tarpos, vmax);

	std::vector<short> coefficients(16, 0);	//packet

	for (int mot = 0; mot < getNumberOfMotors()-1; ++mot) {
		for (int pol=0; pol< trajectory.number_of_points - 1; pol++) {
            for (int i=0; i < 4; ++i) {
                coefficients[ pol + i] = (trajectory.parameters[mot][pol][i]);
            }
		}
        base->GetMOT()->arr[mot].sendFourSplines(
            trajectory.motors[mot][trajectory.number_of_points - 1],
            static_cast<short>(trajectory.dt/0.01),
            coefficients
            );
	}

	base->startSplineMovement(exactflag);

	if (!wait)
		return;

	bool pos_reached = true;
	KNI::Timer t(timeout), poll_t(POLLFREQUENCY);
	t.Start();
	while (true) {
		if (t.Elapsed())
			throw MotorTimeoutException();
		pos_reached = true;
		poll_t.Start();

		base->recvMPS();
		base->recvGMS();

		for (int idx=0; idx<5; idx++) {
			pos_reached &= (std::abs(trajectory.motors[idx][trajectory.number_of_points - 1] - base->GetMOT()->arr[idx].GetPVP()->pos) < tolerance);
			if (base->GetMOT()->arr[idx].GetPVP()->msf == 40)
				throw MotorCrashException();
		}
		if (pos_reached)
			break;

		poll_t.WaitUntilElapsed();
	}

}

// Linear movement with multiple splines
void CLMBase::movLM2P(double X1, double Y1, double Z1, double Ph1,
		double Th1, double Ps1, double X2, double Y2, double Z2, double Ph2,
		double Th2, double Ps2, bool exactflag, double vmax, bool wait,
		int tolerance, long timeout) {

	// check wait parameter
	if (!wait) {
		throw WaitParameterException();
	}

	// check if the robot buffer is ready to receive a new linear movement
	bool motors_ready = false;
	while (!motors_ready) {
		motors_ready = true;
		for (int idx = 0; idx < getNumberOfMotors() - 1; idx++) {
			base->GetMOT()->arr[idx].recvPVP();
			motors_ready &= (base->GetMOT()->arr[idx].GetPVP()->msf != 152);
		}
	}

	// distance between the two points
	double distance = sqrt(pow(X2-X1, 2.0) + pow(Y2-Y1, 2.0) + pow(Z2-Z1, 2.0));

	// acceleration limits in mm/s^2, hardcoded for now
	double acc = 1500;
	double dec = 1500;

	// calculate time for whole movement
	double totaltime = totalTime(distance, acc, dec, vmax);

	// calculate number of splines needed
	double maxtimeperspline = 0.5;
	int steps = (int) (totaltime / maxtimeperspline) + 1;
	short timeperspline;
	timeperspline = (short) floor(100*(totaltime/(steps))+1);

	// calculate intermediate points
	int numberofmotors = getNumberOfMotors();
	int i, j;
	double* timearray = new double [steps + 1];
	double** dataarray = new double* [steps + 1];
	for (i = 0; i < (steps + 1); i++)
		dataarray[i] = new double [numberofmotors];
	double relposition, time, lasttime, x, y, z, phi, theta, psi;
	lasttime = 0;
	std::vector<int> solution(numberofmotors, 0), lastsolution(numberofmotors, 0);
	for (i = 0; i <= steps; i++) {
		// calculate parameters for i-th position
		if(i<steps)
			time = 0.01 * i * (double)timeperspline;
		else
			time = totaltime;

		relposition = relPosition((double) time, distance, acc, dec, vmax);
		x = X1 + relposition * (X2 - X1);
		y = Y1 + relposition * (Y2 - Y1);
		z = Z1 + relposition * (Z2 - Z1);
		phi = Ph1 + relposition * (Ph2 - Ph1);
		theta = Th1 + relposition * (Th2 - Th1);
		psi = Ps1 + relposition * (Ps2 - Ps1);

		// check kinematics
		try {
			IKCalculate(x, y, z, phi, theta, psi, solution.begin());
		} catch(Exception NoSolutionException) {
			throw KNI::NoSolutionException();
		}

		// store data
		for (j = 0; j < numberofmotors; j++) {
			dataarray[i][j] = (double) solution.at(j);
		}
		timearray[i] = time;

		// check joint speeds, stop program if failed
		if (time > 0) {
			if (!checkJointSpeed(lastsolution, solution, (time - lasttime))) {
				throw JointSpeedException();
			}
		}
		lasttime = time;
		lastsolution.clear();
		lastsolution.assign(solution.begin(), solution.end());
	}

	// calculate spline
	short*** parameters = new short** [steps];
	for (i = 0; i < steps; i++)
		parameters[i] = new short* [numberofmotors];
	for (i = 0; i < steps; i++)
		for (j = 0; j < numberofmotors; j++)
			parameters[i][j] = new short[7];
	double* encoderarray = new double [steps + 1];
	double* arr_p1 = new double [steps];
	double* arr_p2 = new double [steps];
	double* arr_p3 = new double [steps];
	double* arr_p4 = new double [steps];
	double s_time;
	for (i = 0; i < numberofmotors; i++) {
		// one motor at a time
		for (j = 0; j <= steps; j++) {
			encoderarray[j] = dataarray[j][i];
		}
		splineCoefficients(steps, timearray, encoderarray, arr_p1, arr_p2,
			arr_p3, arr_p4);
		// store parameters for G command to motor i
		for (j = 0; j < steps; j++) {
			// motor number
			parameters[j][i][0] = (short) i;
			// targetencoder
			parameters[j][i][1] = (short) encoderarray[j + 1];
			// robot time (in 10ms steps)
			s_time = (timearray[j + 1] - timearray[j]) * 100;
			if(j < steps-1)
				parameters[j][i][2] = (short) timeperspline;
			else
				parameters[j][i][2] = (short) s_time;
			// the four spline coefficients
			// the actual position, round
			parameters[j][i][3] = (short) floor(arr_p1[j] + 0.5);
			// shift to be firmware compatible and round
			parameters[j][i][4] = (short) floor(64 * arr_p2[j] / s_time +
				0.5);
			parameters[j][i][5] = (short) floor(1024 * arr_p3[j] /
				pow(s_time, 2) + 0.5);
			parameters[j][i][6] = (short) floor(32768 * arr_p4[j] /
				pow(s_time, 3) + 0.5);
		}
	}

	// send spline
	long spline_timeout = (long) parameters[0][0][2] * 10;// - 2;
	KNI::Timer t(timeout), spline_t(spline_timeout);
	t.Start();
	spline_t.Start();
	//wait for motor
	int wait_timeout = 5000;
	// get master firmware version and revision
	short version, revision;
	GetBase()->getMasterFirmware(&version, &revision);
	if (mKatanaType == 400) {
		int totalsplinetime = 0;
		for (i = 0; i < steps; i++) {
			// ignore further steps if timeout elapsed
			if (t.Elapsed())
				break;
			// send parameters
			for(j = 0; j < numberofmotors; j++) {
				sendSplineToMotor((unsigned short) parameters[i][j][0],
					parameters[i][j][1], parameters[i][j][2],
					parameters[i][j][3], parameters[i][j][4],
					parameters[i][j][5], parameters[i][j][6]);
			}
			totalsplinetime += parameters[i][0][2] * 10;
			// start movement
			if (i == (steps-1)) {
				// last spline, start movement
				startSplineMovement(exactflag, 1);
			} else if (totalsplinetime < 400) {
				// more splines following, do not start movement yet
				startSplineMovement(exactflag, 2);
			} else {
				// more splines following, start movement
				startSplineMovement(exactflag, 0);
			}
		}
	} else {
		for (i = 0; i < steps; i++) {
			// ignore further steps if timeout elapsed
			if (t.Elapsed())
				break;
			// wait for motor to finish movement
			waitForMotor(0, 0, tolerance, 2, wait_timeout);
			// send parameters
			for(j = 0; j < numberofmotors; j++) {
				sendSplineToMotor((unsigned short) parameters[i][j][0],
					parameters[i][j][1], parameters[i][j][2],
					parameters[i][j][3], parameters[i][j][4],
					parameters[i][j][5], parameters[i][j][6]);
			}
			// start movement
			startSplineMovement(exactflag);
		}
	}

	// cleanup
	delete timearray;
    for (i = 0; i < (steps + 1); i++)
        delete dataarray[i];
	delete dataarray;
    for (i = 0; i < steps; i++)
        for (j = 0; j < numberofmotors; j++)
            delete parameters[i][j];
    for (i = 0; i < steps; i++)
        delete parameters[i];
	delete parameters;
	delete encoderarray;
	delete arr_p1;
	delete arr_p2;
	delete arr_p3;
	delete arr_p4;

	waitForMotor(0, 0, tolerance, 2, wait_timeout);
	//std::cout << "linear movement finished" << std::endl;

}

double CLMBase::totalTime(double distance, double acc, double dec,
		double vmax) {

	// minimum distance to reach vmax
	double borderdistance = pow(vmax, 2.0) / 2.0 * (1 / acc + 1 / dec);

	double time;
	if (distance > borderdistance) {
		time = distance / vmax + vmax / 2.0 * (1 / acc + 1 / dec);
	} else {
		time = sqrt(8 * distance / (acc + dec));
	}

	return time;
}


double CLMBase::relPosition(double reltime, double distance, double acc, double dec,
		double vmax) {

	// minimum distance to reach vmax
	double borderdistance = pow(vmax, 2.0) / 2.0 * (1 / acc + 1 / dec);

	double position, totaltime, time;
	if (distance > borderdistance) { // vmax reached during movement
		totaltime = distance / vmax + vmax / 2.0 * (1 / acc + 1 / dec);
		time = reltime ;
		if (time < vmax / acc) { // accelerating
			position = acc / 2 * pow(time, 2);
		} else if (time < totaltime - (vmax / dec)) { // at vmax
			position = vmax * (time - vmax / acc / 2);
		} else { // decelerating
			position = distance - dec * (pow(time, 2) / 2 - totaltime * time +
				pow(totaltime, 2) /2);
		}
	} else { // vmax not reached during movement
		totaltime = sqrt(8 * distance / (acc + dec));
		time = reltime ;
		if (time < totaltime * dec / (acc + dec)) { // accelerating
			position = acc / 2 * pow(time, 2);
		} else { // decelerating
			position = distance - dec * (pow(time, 2) / 2 - totaltime * time +
				pow(totaltime, 2) /2);
		}
	}

	return (position / distance);
}

void CLMBase::splineCoefficients(int steps, double *timearray, double *encoderarray,
		double *arr_p1, double *arr_p2, double *arr_p3, double *arr_p4) {

	int i, j; // countervariables

	// calculate time differences between points and b-coefficients
	double* deltatime = new double [steps];
	double* b = new double [steps];
	for (i = 0; i < steps; i++) {
		deltatime[i] = timearray[i + 1] - timearray[i];
		b[i] = 1.0 / deltatime[i];
	}

	// calculate a-coefficients
	double* a = new double [steps - 1];
	for (i = 0; i < (steps - 1); i++) {
		a[i] = (2 / deltatime[i]) + (2 / deltatime[i + 1]);
	}

	// build up the right hand side of the linear system
	double* c = new double [steps];
	double* d = new double [steps + 1];
	d[0] = 0; // f_1' and f_n' equal zero
	d[steps] = 0;
	for (i = 0; i < steps; i++) {
		c[i] = (encoderarray[i + 1] - encoderarray[i]) / (deltatime[i] * deltatime[i]);
	}
	for (i = 0; i < (steps - 1); i++) {
		d[i + 1] = 3 * (c[i] + c[i + 1]);
	}

	// compose A * f' = d
	double** Alin = new double* [steps - 1]; // last column of Alin is right hand side
	for (i = 0; i < (steps - 1); i++)
		Alin[i] = new double [steps];
	// fill with zeros
	for (i = 0; i < (steps - 1); i++) {
		for (j = 0; j < steps; j++) {
			Alin[i][j] = 0.0;
		}
	}
	// insert values
	for (i = 0; i < (steps - 1); i++) {
		if (i == 0) {
			Alin[0][0] = a[0];
			Alin[0][1] = b[1];
			Alin[0][steps - 1] = d[1];
		} else {
			Alin[i][i - 1] = b[i];
			Alin[i][i] = a[i];
			Alin[i][i + 1] = b[i + 1];
			Alin[i][steps - 1] = d[i + 1];
		}
	}

	// solve linear equation
	boost::numeric::ublas::matrix<double> ublas_A(steps - 1, steps - 1);
	boost::numeric::ublas::matrix<double> ublas_b(steps - 1, 1);
	for (i = 0; i < (steps - 1); i++) {
		for (j = 0; j < (steps - 1); j++) {
			ublas_A(i, j) = Alin[i][j];
		}
		ublas_b(i, 0) = Alin[i][steps - 1];
	}
	boost::numeric::ublas::permutation_matrix<unsigned int> piv(steps - 1);
	lu_factorize(ublas_A, piv);
	lu_substitute(ublas_A, piv, ublas_b);

	// save result in derivatives array
	double* derivatives = new double [steps + 1];
	derivatives[0] = 0;
	for (i = 0; i < (steps - 1); i++) {
		derivatives[i + 1] = ublas_b(i, 0);
	}
	derivatives[steps] = 0;
	// build the hermite polynom with difference scheme
	// Q(t) = a0 + (b0 + (c0 + d0 * t) * (t - 1)) * t = a0 + (b0 - c0) * t +
	//   (c0 - d0) * t^2 + d0 * t^3 = p0 + p1 * t + p2 * t^2 + p3 * t^3
	double a0, b0, c0, d0;
	for (i = 0; i < steps; i++) {
		a0 = encoderarray[i];
		b0 = encoderarray[i + 1] - a0;
		c0 = b0 - deltatime[i] * derivatives[i];
		d0 = deltatime[i] * (derivatives[i + 1] + derivatives[i]) - 2 * b0;
		arr_p1[i] = a0;
		arr_p2[i] = b0 - c0;
		arr_p3[i] = c0 - d0;
		arr_p4[i] = d0;
	}
}

bool CLMBase::checkJointSpeed(std::vector<int> lastsolution,
		std::vector<int> solution, double time) {

	const int speedlimit = 180; // encoder per 10ms

	bool speedok = true;
	int localtime = (int) (time * 100); // in 10ms
	int speed;
	int i;

	// check speed for every motor
	for (i = 0; i < ((int) solution.size()); i++) {
		speed = abs(solution.at(i) - lastsolution.at(i)) / localtime;
		if (speed > speedlimit)
			speedok = false;
	}

	return speedok;
}

void CLMBase::movLM(double X, double Y, double Z,
                    double Al, double Be, double Ga,
                    bool exactflag, double vmax, bool wait, int tolerance, long timeout) {

	double arr_tarpos[6] = {X, Y, Z, Al, Be, Ga};
	// target position in cartesian units
	double arr_actpos[6];
	// current position in cartesian units, NO REFRESH, SINCE ALREADY DONE IN moveRobotLinearTo()
	getCoordinates(arr_actpos[0], arr_actpos[1], arr_actpos[2], arr_actpos[3], arr_actpos[4], arr_actpos[5], false);

	movLM2P(arr_actpos[0], arr_actpos[1], arr_actpos[2], arr_actpos[3], arr_actpos[4], arr_actpos[5],
	        arr_tarpos[0], arr_tarpos[1], arr_tarpos[2], arr_tarpos[3], arr_tarpos[4], arr_tarpos[5],
	        exactflag, vmax, wait, tolerance, timeout);

}

void CLMBase::moveRobotLinearTo(double x, double y, double z, double phi, double theta, double psi, bool waitUntilReached, int waitTimeout) {
	// Initialize if not already done
	if(!_isInitialized)
		initLM();
	// refresh encoders to make sure we use the right actual position
	base->recvMPS();

	movLM(x, y, z, phi, theta, psi, _activatePositionController, _maximumVelocity, waitUntilReached, 100, waitTimeout);
}

void CLMBase::moveRobotLinearTo(std::vector<double> coordinates, bool waitUntilReached, int waitTimeout) {
	moveRobotLinearTo( coordinates.at(0), coordinates.at(1), coordinates.at(2), coordinates.at(3), coordinates.at(4), coordinates.at(5), waitUntilReached, waitTimeout);
}

// set maximum linear velocity in mm/s
void CLMBase::setMaximumLinearVelocity(double maximumVelocity) {
	if (maximumVelocity < 1)
		maximumVelocity = 1;
	if (maximumVelocity > 300)
		maximumVelocity = 300;
	_maximumVelocity = maximumVelocity;
}
double CLMBase::getMaximumLinearVelocity() const {
	return _maximumVelocity;
}

void CLMBase::setActivatePositionController(bool activate) {
	_activatePositionController = activate;
}
bool CLMBase::getActivatePositionController() {
	return _activatePositionController;
}

/*

TRetBLEND CLMBase::movLMBlend(double X1, double Y1, double Z1,
                              double Al1, double Be1, double Ga1,
                              double X2, double Y2, double Z2,
                              double Al2, double Be2, double Ga2,
                              double vmax, long tightness) {


	double		amax = 1500;
	double		kappa = 7.5;

	double		arr_actpos[6];
	DKApos(arr_actpos);

	blendtrajectory.number_of_referencepoints = 3; // only for prototype

	blendtrajectory.referencepoints[0].X = arr_actpos[0];
	blendtrajectory.referencepoints[0].Y = arr_actpos[1];
	blendtrajectory.referencepoints[0].Z = arr_actpos[2];
	blendtrajectory.referencepoints[0].Al = arr_actpos[3];
	blendtrajectory.referencepoints[0].Be = arr_actpos[4];
	blendtrajectory.referencepoints[0].Ga = arr_actpos[5];

	blendtrajectory.referencepoints[1].X = X1;
	blendtrajectory.referencepoints[1].Y = Y1;
	blendtrajectory.referencepoints[1].Z = Z1;
	blendtrajectory.referencepoints[1].Al = Al1;
	blendtrajectory.referencepoints[1].Be = Be1;
	blendtrajectory.referencepoints[1].Ga = Ga1;

	blendtrajectory.referencepoints[2].X = X2;
	blendtrajectory.referencepoints[2].Y = Y2;
	blendtrajectory.referencepoints[2].Z = Z2;
	blendtrajectory.referencepoints[2].Al = Al2;
	blendtrajectory.referencepoints[2].Be = Be2;
	blendtrajectory.referencepoints[2].Ga = Ga2;

	// Calculate blend traces
	if (blend_calculate_blendtraces(amax, vmax, tightness) != BLEND_SUCCESSFUL)
		return BLEND_NOTPOSSIBLE;

	// Calculate points for splines
	if (blend_fill_splinepoints(kappa, amax, vmax) != BLEND_SUCCESSFUL)
		return BLEND_DECNOTPOSSIBLE;

	return BLEND_SUCCESSFUL;

}

TRetBLEND CLMBase::blend_calculate_blendtraces(double amax, double vmax, long tightness) {

	short number_of_blends = blendtrajectory.number_of_referencepoints - 1;
	blendtrajectory.number_of_blends = number_of_blends;

	TPoint3D point1;
	TPoint3D point2;
	TPoint3D point3;

	for (int trace = 0; trace < number_of_blends - 1; trace++) {

		double	 dist;

		point1.X = blendtrajectory.referencepoints[trace].X;
		point1.Y = blendtrajectory.referencepoints[trace].Y;
		point1.Z = blendtrajectory.referencepoints[trace].Z;

		point2.X = blendtrajectory.referencepoints[trace+1].X;
		point2.Y = blendtrajectory.referencepoints[trace+1].Y;
		point2.Z = blendtrajectory.referencepoints[trace+1].Z;

		point3.X = blendtrajectory.referencepoints[trace+2].X;
		point3.Y = blendtrajectory.referencepoints[trace+2].Y;
		point3.Z = blendtrajectory.referencepoints[trace+2].Z;

		TPoint3D dist12;

		dist12.X = point2.X - point1.X;
		dist12.Y = point2.Y - point1.Y;
		dist12.Z = point2.Z - point1.Z;

		dist = pow(pow(dist12.X,2)+pow(dist12.Y,2)+pow(dist12.Z,2),0.5);

		blendtrajectory.blendtrace[trace].p1p2n.X = dist12.X/dist;
		blendtrajectory.blendtrace[trace].p1p2n.Y = dist12.Y/dist;
		blendtrajectory.blendtrace[trace].p1p2n.Z = dist12.Z/dist;

		blendtrajectory.blendtrace[trace].V1A.X = blendtrajectory.blendtrace[trace].p1p2n.X * vmax;
		blendtrajectory.blendtrace[trace].V1A.Y = blendtrajectory.blendtrace[trace].p1p2n.Y * vmax;
		blendtrajectory.blendtrace[trace].V1A.Z = blendtrajectory.blendtrace[trace].p1p2n.Z * vmax;

		TPoint3D dist23;

		dist23.X = point3.X - point2.X;
		dist23.Y = point3.Y - point2.Y;
		dist23.Z = point3.Z - point2.Z;

		dist = pow(pow(dist23.X,2)+pow(dist23.Y,2)+pow(dist23.Z,2),0.5);

		// p2p3n = dist23.X/dist
		blendtrajectory.blendtrace[trace].p2p3n.X = dist23.X/dist;
		blendtrajectory.blendtrace[trace].p2p3n.Y = dist23.Y/dist;
		blendtrajectory.blendtrace[trace].p2p3n.Z = dist23.Z/dist;

		// V1A = p2p3n * vmax
		blendtrajectory.blendtrace[trace].V1B.X = blendtrajectory.blendtrace[trace].p2p3n.X * vmax;
		blendtrajectory.blendtrace[trace].V1B.Y = blendtrajectory.blendtrace[trace].p2p3n.Y * vmax;
		blendtrajectory.blendtrace[trace].V1B.Z = blendtrajectory.blendtrace[trace].p2p3n.Z * vmax;

		// P1A = point2 - tightness * p1p2n
		blendtrajectory.blendtrace[trace].P1A.X = point2.X - tightness * blendtrajectory.blendtrace[trace].p1p2n.X;
		blendtrajectory.blendtrace[trace].P1A.Y = point2.Y - tightness * blendtrajectory.blendtrace[trace].p1p2n.Y;
		blendtrajectory.blendtrace[trace].P1A.Z = point2.Z - tightness * blendtrajectory.blendtrace[trace].p1p2n.Z;

		// P1B = point2 - tightness * p2p3n
		blendtrajectory.blendtrace[trace].P1B.X = point2.X - tightness * blendtrajectory.blendtrace[trace].p2p3n.X;
		blendtrajectory.blendtrace[trace].P1B.Y = point2.Y - tightness * blendtrajectory.blendtrace[trace].p2p3n.Y;
		blendtrajectory.blendtrace[trace].P1B.Z = point2.Z - tightness * blendtrajectory.blendtrace[trace].p2p3n.Z;

		// b1 = P1A
		blendtrajectory.blendtrace[trace].b1.X = blendtrajectory.blendtrace[trace].P1B.X;
		blendtrajectory.blendtrace[trace].b1.Y = blendtrajectory.blendtrace[trace].P1B.Y;
		blendtrajectory.blendtrace[trace].b1.Z = blendtrajectory.blendtrace[trace].P1B.Z;

		double tau = tightness/vmax;

		// m1 = 2 * tau * V1A
		blendtrajectory.blendtrace[trace].m1.X = 2 * tau * blendtrajectory.blendtrace[trace].V1A.X;
		blendtrajectory.blendtrace[trace].m1.Y = 2 * tau * blendtrajectory.blendtrace[trace].V1A.Y;
		blendtrajectory.blendtrace[trace].m1.Z = 2 * tau * blendtrajectory.blendtrace[trace].V1A.Z;

		// b2 = P1B - 2 * tau * V1B
		blendtrajectory.blendtrace[trace].b2.X = blendtrajectory.blendtrace[trace].P1B.X - 2 * tau * blendtrajectory.blendtrace[trace].V1B.X;
		blendtrajectory.blendtrace[trace].b2.Y = blendtrajectory.blendtrace[trace].P1B.Y - 2 * tau * blendtrajectory.blendtrace[trace].V1B.Y;
		blendtrajectory.blendtrace[trace].b2.Z = blendtrajectory.blendtrace[trace].P1B.Z - 2 * tau * blendtrajectory.blendtrace[trace].V1B.Z;

		// m2 = 2 * tau * V1B
		blendtrajectory.blendtrace[trace].m2.X = 2 * tau * blendtrajectory.blendtrace[trace].V1B.X;
		blendtrajectory.blendtrace[trace].m2.Y = 2 * tau * blendtrajectory.blendtrace[trace].V1B.Y;
		blendtrajectory.blendtrace[trace].m2.Z = 2 * tau * blendtrajectory.blendtrace[trace].V1B.Z;

		// Minimum distance needed to reach the maximun speed (vmax) with the acceleration amax
		double dGrenz = (pow(vmax,2)) / ( 2 * amax);

		if (trace = 0) { // first trace

			// distBA = P1A - point1
			blendtrajectory.blendtrace[trace].distBA = pow(
			            pow(blendtrajectory.blendtrace[trace].P1A.X - point1.X,2) +
			            pow(blendtrajectory.blendtrace[trace].P1A.Y - point1.Y,2) +
			            pow(blendtrajectory.blendtrace[trace].P1A.Z - point1.Z,2), 0.5);

			if (blendtrajectory.blendtrace[trace].distBA < dGrenz)
				return BLEND_NOTPOSSIBLE;

			// tA = distBA/vmax + vmax / 2 * amax
			blendtrajectory.blendtrace[trace].tA = blendtrajectory.blendtrace[trace].distBA / vmax + vmax / (2 * amax);

		} else {		// other traces

			// distBA = P1A - P1Bsub-1
			blendtrajectory.blendtrace[trace].distBA = pow(
			            pow(blendtrajectory.blendtrace[trace].P1A.X - blendtrajectory.blendtrace[trace-1].P1B.X,2) +
			            pow(blendtrajectory.blendtrace[trace].P1A.Y - blendtrajectory.blendtrace[trace-1].P1B.Y,2) +
			            pow(blendtrajectory.blendtrace[trace].P1A.Z - blendtrajectory.blendtrace[trace-1].P1B.Z,2), 0.5);

			// tA = tBsub-1 + distBA / vmax
			blendtrajectory.blendtrace[trace].tA = blendtrajectory.blendtrace[trace-1].tB + blendtrajectory.blendtrace[trace].distBA / vmax;
		}

		// tB = tA + 2 * tau
		blendtrajectory.blendtrace[trace].tB = blendtrajectory.blendtrace[trace].tA + 2 * tau;

	}

	// distBA = Point3 - P2B
	blendtrajectory.blendtrace[number_of_blends-1].distBA = pow(
	            pow(point3.X - blendtrajectory.blendtrace[number_of_blends-2].P1B.X,2) +
	            pow(point3.Y - blendtrajectory.blendtrace[number_of_blends-2].P1B.Y,2) +
	            pow(point3.Z - blendtrajectory.blendtrace[number_of_blends-2].P1B.Z,2), 0.5);

	blendtrajectory.tEnd = blendtrajectory.blendtrace[number_of_blends-2].tB +
	                       blendtrajectory.blendtrace[number_of_blends-1].distBA / vmax + vmax/(2*amax);

	return BLEND_SUCCESSFUL;

}

TRetBLEND CLMBase::blend_fill_splinepoints(double kappa, double amax, double vmax) {

	double maxtime = 0.5;
	blendtrajectory.number_of_splines = (short) ((blendtrajectory.tEnd / (maxtime * 4)) + 1);

	blendtrajectory.number_of_splinepoints = blendtrajectory.number_of_splines * 4 + 1;

	for (int spoint=0; spoint < blendtrajectory.number_of_splinepoints; spoint++) {

		double t = spoint / (blendtrajectory.number_of_splinepoints - 1) * blendtrajectory.tEnd;
		blendtrajectory.splinepoints[spoint].time = t;

		short blendtrace_pos = 0;

		// search for the right blend trace and check if the trace
		// should be linear or curve for this point

		while (t > blendtrajectory.blendtrace[blendtrace_pos].tB &&
		        blendtrace_pos <= blendtrajectory.number_of_blends)
			blendtrace_pos++;

		bool linear = false;
		if (t < blendtrajectory.blendtrace[blendtrace_pos].tA ||
		        blendtrace_pos == blendtrajectory.number_of_blends - 1)
			linear = true;

		if (!linear) { // curve part of the trace

			// s = (t - tA) / (tB - tA)
			double s = (t - blendtrajectory.blendtrace[blendtrace_pos].tA) /
			           (blendtrajectory.blendtrace[blendtrace_pos].tB - blendtrajectory.blendtrace[blendtrace_pos].tA);

			double p1x = blendtrajectory.blendtrace[blendtrace_pos].b1.X +
			             s * blendtrajectory.blendtrace[blendtrace_pos].m1.X;
			double p1y = blendtrajectory.blendtrace[blendtrace_pos].b1.Y +
			             s * blendtrajectory.blendtrace[blendtrace_pos].m1.Y;
			double p1z = blendtrajectory.blendtrace[blendtrace_pos].b1.Z +
			             s * blendtrajectory.blendtrace[blendtrace_pos].m1.Z;

			double p2x = blendtrajectory.blendtrace[blendtrace_pos].b2.X +
			             s * blendtrajectory.blendtrace[blendtrace_pos].m2.X;
			double p2y = blendtrajectory.blendtrace[blendtrace_pos].b2.Y +
			             s * blendtrajectory.blendtrace[blendtrace_pos].m2.Y;
			double p2z = blendtrajectory.blendtrace[blendtrace_pos].b2.Z +
			             s * blendtrajectory.blendtrace[blendtrace_pos].m2.Z;

			double alpha = (6*(pow(s,5))) - (15*(pow(s,4))) + (10 * (pow(s,3)));
			double beta = (pow(s,6)) - (3*(pow(s,5))) + (3*(pow(s,4))) - (pow(s,3));

			blendtrajectory.splinepoints[spoint].point.X = p1x + (alpha*(p2x-p1x)) -
			        (kappa * beta * (blendtrajectory.blendtrace[blendtrace_pos].m2.X - blendtrajectory.blendtrace[blendtrace_pos].m1.X));

			blendtrajectory.splinepoints[spoint].point.Y = p1y + (alpha*(p2y-p1y)) -
			        (kappa * beta * (blendtrajectory.blendtrace[blendtrace_pos].m2.Y - blendtrajectory.blendtrace[blendtrace_pos].m1.Y));

			blendtrajectory.splinepoints[spoint].point.Z = p1z + (alpha*(p2z-p1z)) -
			        (kappa * beta * (blendtrajectory.blendtrace[blendtrace_pos].m2.Z - blendtrajectory.blendtrace[blendtrace_pos].m1.Z));

			blendtrajectory.splinepoints[spoint].point.Al = blendtrajectory.referencepoints[blendtrace_pos+1].Al;
			blendtrajectory.splinepoints[spoint].point.Be = blendtrajectory.referencepoints[blendtrace_pos+1].Be;
			blendtrajectory.splinepoints[spoint].point.Ga = blendtrajectory.referencepoints[blendtrace_pos+1].Ga;

		} else {	// linear trace
			if (blendtrace_pos==0) { // first trace

				double I = blend_Ivontacc(t/blendtrajectory.blendtrace[blendtrace_pos].tA, blendtrajectory.blendtrace[blendtrace_pos].distBA, amax, vmax);

				blendtrajectory.splinepoints[spoint].point.X = blendtrajectory.referencepoints[blendtrace_pos].X +
				        (I * (blendtrajectory.blendtrace[blendtrace_pos].P1A.X - blendtrajectory.referencepoints[blendtrace_pos].X));

				blendtrajectory.splinepoints[spoint].point.Y = blendtrajectory.referencepoints[blendtrace_pos].Y +
				        (I * (blendtrajectory.blendtrace[blendtrace_pos].P1A.Y - blendtrajectory.referencepoints[blendtrace_pos].Y));

				blendtrajectory.splinepoints[spoint].point.Z = blendtrajectory.referencepoints[blendtrace_pos].Z +
				        (I * (blendtrajectory.blendtrace[blendtrace_pos].P1A.Z - blendtrajectory.referencepoints[blendtrace_pos].Z));

				blendtrajectory.splinepoints[spoint].point.Al = blendtrajectory.referencepoints[blendtrace_pos].Al +
				        (I * (blendtrajectory.referencepoints[blendtrace_pos+1].Al - blendtrajectory.referencepoints[blendtrace_pos].Al));

				blendtrajectory.splinepoints[spoint].point.Be = blendtrajectory.referencepoints[blendtrace_pos].Be +
				        (I * (blendtrajectory.referencepoints[blendtrace_pos+1].Be - blendtrajectory.referencepoints[blendtrace_pos].Be));

				blendtrajectory.splinepoints[spoint].point.Ga = blendtrajectory.referencepoints[blendtrace_pos].Ga +
				        (I * (blendtrajectory.referencepoints[blendtrace_pos+1].Ga - blendtrajectory.referencepoints[blendtrace_pos].Ga));

			} else {
				if (blendtrace_pos == blendtrajectory.number_of_blends - 1) { // last trace

					double I;

					if (blend_Ivontdec((t/blendtrajectory.blendtrace[blendtrace_pos-2].tB)/
					                   (blendtrajectory.tEnd - blendtrajectory.blendtrace[blendtrace_pos-1].tB),
					                   blendtrajectory.blendtrace[blendtrace_pos-1].distBA,amax,vmax, &I) != BLEND_SUCCESSFUL)
						return BLEND_DECNOTPOSSIBLE;

					blendtrajectory.splinepoints[spoint].point.X = blendtrajectory.blendtrace[blendtrajectory.number_of_blends-1].P1B.X +
					        (I * (blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-1].X - blendtrajectory.blendtrace[blendtrajectory.number_of_blends-1].P1B.X));

					blendtrajectory.splinepoints[spoint].point.X = blendtrajectory.blendtrace[blendtrajectory.number_of_blends - 1].P1B.Y +
					        (I * (blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-1].Y - blendtrajectory.blendtrace[blendtrajectory.number_of_blends-1].P1B.Y));

					blendtrajectory.splinepoints[spoint].point.X = blendtrajectory.blendtrace[blendtrajectory.number_of_blends - 1].P1B.Z +
					        (I * (blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-1].Z - blendtrajectory.blendtrace[blendtrajectory.number_of_blends-1].P1B.Z));

					blendtrajectory.splinepoints[spoint].point.Al = blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-2].Al +
					        (I * (blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-1].Al - blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-2].Al));

					blendtrajectory.splinepoints[spoint].point.Be = blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-2].Be +
					        (I * (blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-1].Be - blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-2].Be));

					blendtrajectory.splinepoints[spoint].point.Al = blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-2].Ga +
					        (I * (blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-1].Ga - blendtrajectory.referencepoints[blendtrajectory.number_of_referencepoints-2].Ga));

				} else { // other traces

					// I = (t - tBsub-1) / (tA - tBsub-1)
					double I = (t - blendtrajectory.blendtrace[blendtrace_pos-1].tB) /
					           (blendtrajectory.blendtrace[blendtrace_pos].tA - blendtrajectory.blendtrace[blendtrace_pos-1].tB);

					blendtrajectory.splinepoints[spoint].point.X = blendtrajectory.blendtrace[blendtrace_pos-1].P1B.X +
					        (I * (blendtrajectory.blendtrace[blendtrace_pos].P1A.X - blendtrajectory.blendtrace[blendtrace_pos-1].P1B.X));

					blendtrajectory.splinepoints[spoint].point.Y = blendtrajectory.blendtrace[blendtrace_pos-1].P1B.Y +
					        (I * (blendtrajectory.blendtrace[blendtrace_pos].P1A.Y - blendtrajectory.blendtrace[blendtrace_pos-1].P1B.Y));

					blendtrajectory.splinepoints[spoint].point.Z = blendtrajectory.blendtrace[blendtrace_pos-1].P1B.Z +
					        (I * (blendtrajectory.blendtrace[blendtrace_pos].P1A.Y - blendtrajectory.blendtrace[blendtrace_pos-1].P1B.Z));

					blendtrajectory.splinepoints[spoint].point.Al = blendtrajectory.referencepoints[blendtrace_pos].Al +
					        (I * (blendtrajectory.referencepoints[blendtrace_pos+1].Al - blendtrajectory.referencepoints[blendtrace_pos].Al));

					blendtrajectory.splinepoints[spoint].point.Be = blendtrajectory.referencepoints[blendtrace_pos].Be +
					        (I * (blendtrajectory.referencepoints[blendtrace_pos+1].Be - blendtrajectory.referencepoints[blendtrace_pos].Be));

					blendtrajectory.splinepoints[spoint].point.Ga = blendtrajectory.referencepoints[blendtrace_pos].Ga +
					        (I * (blendtrajectory.referencepoints[blendtrace_pos+1].Ga - blendtrajectory.referencepoints[blendtrace_pos].Ga));

				}
			}
		}
	}

	return BLEND_SUCCESSFUL;
}

double CLMBase::blend_Ivontacc(double tp, double dist, double amax, double vmax) {

	double T0;
	double pos;
	double t;

	double dgrenz = pow(vmax,2) / (2 * amax);

	if (dist > dgrenz) {

		T0 = (dist/vmax) + (vmax / (2 * amax));
		t = tp * T0;

		if (t < (vmax/amax)) {
			pos = amax /(2 * pow(t,2));
		} else {
			pos = vmax * (t - (0.5 * vmax / amax));
		}

	} else {

		T0 = pow((2 * dist / amax),2);
		t = tp * T0;
		pos = amax / 2 * pow(t,2);

	};

	return (pos/dist);
}

TRetBLEND CLMBase::blend_Ivontdec(double tp, double dist, double amax, double vmax, double* I) {

	double T0;
	double pos;
	double t;
	double tm;

	double dgrenz = pow(vmax,2) / (2 * amax);

	if (dist < dgrenz)
		return BLEND_DECNOTPOSSIBLE;

	T0 = (dist / vmax) + ( vmax /2 * amax);
	t = tp * T0;
	tm = T0 - (vmax /amax);

	if (t<tm) {
		pos = vmax * t;
	} else {
		pos = dist - (0.5 * amax * pow((T0-t),2));
	};

	*I = (double)(pos/dist);

	return BLEND_SUCCESSFUL;

}

*/

