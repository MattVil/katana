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


#include "KNI/kmlExt.h"
#include "KNI/kmlFactories.h"

#include "common/MathHelperFunctions.h"
#include "common/Timer.h"

#include <iostream>
#include <algorithm>
#include <vector>

#define max(a,b) (((a)>(b))?(a):(b))

#include <fstream>


/// Polling position every POLLFREQUENCY milliseconds
const int POLLFREQUENCY = 300;

void CKatana::inc(long idx, int dif, bool wait, int tolerance, long timeout) {
	base->GetMOT()->arr[idx].inc(dif,wait,tolerance,timeout);
}

void CKatana::dec(long idx, int dif, bool wait, int tolerance, long timeout) {
	base->GetMOT()->arr[idx].dec(dif,wait,tolerance,timeout);
}

void CKatana::mov(long idx, int tar, bool wait, int tolerance, long timeout) {
	base->GetMOT()->arr[idx].mov(tar, wait,tolerance,timeout);
}



void CKatana::incDegrees(long idx, double dif, bool wait, int tolerance, long timeout) {
	base->GetMOT()->arr[idx].incDegrees(dif,wait,tolerance,timeout);
}

void CKatana::decDegrees(long idx, double dif, bool wait, int tolerance, long timeout) {
	base->GetMOT()->arr[idx].decDegrees(dif,wait,tolerance,timeout);
}

void CKatana::movDegrees(long idx, double tar, bool wait, int tolerance, long timeout) {
	base->GetMOT()->arr[idx].movDegrees(tar,wait,tolerance,timeout);
}



void CKatana::setTPSP(long idx, int tar) {
	base->GetMOT()->arr[idx].setTPSP(tar);
}

void CKatana::resetTPSP() {
	for (int i=0; i < getNumberOfMotors(); i++)
		base->GetMOT()->arr[i].resetTPSP();
}

void CKatana::sendTPSP(bool wait, long timeout) {

	bool pos_reached;

	base->sendTPSP();

	if (!wait)
		return;

	KNI::Timer t(timeout);
	t.Start();
	while (true) {
		if (t.Elapsed())
			throw MotorTimeoutException();

		pos_reached = true;
		for (int idx=0; idx<5; idx++) {

			base->GetMOT()->arr[idx].recvPVP();
			pos_reached &= !base->GetMOT()->arr[idx].GetFreedom() ||
			               abs(base->GetMOT()->arr[idx].GetTPS()->tarpos - base->GetMOT()->arr[idx].GetPVP()->pos)
			               < base->GetMOT()->arr[idx].GetEncoderTolerance();
		}

		if (pos_reached) {
			// clear the freedom flag of each motor
			for (int idx=0; idx<5; idx++) {
				base->GetMOT()->arr[idx].resetTPSP();
			}
			return;
		}
	}

	throw ParameterWritingException("TPSP");

}



void CKatana::setTPSPDegrees(long idx, double tar) {
	base->GetMOT()->arr[idx].setTPSPDegrees(tar);
}


void CKatana::create(const char* configurationFile, CCplBase* protocol) {
	KNI::kmlFactory infos;
	if(!infos.openFile(configurationFile)) {
		throw ConfigFileOpenException(configurationFile);
	}
	create(&infos, protocol);
}

void CKatana::create(KNI::kmlFactory* infos, CCplBase* protocol) {
	base->init( infos->getGNL(), infos->getMOT(), infos->getSCT(), infos->getEFF(), protocol);

	for(int i=0; i<getNumberOfMotors(); ++i) {
		TMotInit init = infos->getMotInit(i);

		base->GetMOT()->arr[i].setInitialParameters(KNI_MHF::deg2rad(init.angleOffset), KNI_MHF::deg2rad(init.angleRange), init.encodersPerCycle, init.encoderOffset, init.rotationDirection);

		TMotCLB clb = infos->getMotCLB(i);
		base->GetMOT()->arr[i].setCalibrationParameters( clb.enable, clb.order, clb.dir, clb.mcf, clb.encoderPositionAfter );

		base->GetMOT()->arr[i].setDYL( infos->getMotDYL(i) );
		base->GetMOT()->arr[i].setSCP( infos->getMotSCP(i) );
	}

	bool gripperIsPresent;
	int gripperOpenEncoders, gripperCloseEncoders;
	infos->getGripperParameters(gripperIsPresent, gripperOpenEncoders, gripperCloseEncoders);
	setGripperParameters(gripperIsPresent, gripperOpenEncoders, gripperCloseEncoders);

}

void CKatana::create(TKatGNL& gnl, TKatMOT& mot, TKatSCT& sct, TKatEFF& eff, CCplBase* protocol) {
	base->init(gnl, mot, sct, eff, protocol);
}



void CKatana::calibrate() {
	//----------------------------------------------------------------//
	//set motors ON before calibrating
	//----------------------------------------------------------------//
	TMotAPS aps;
	for (int i=0; i<getNumberOfMotors(); i++) {
		aps.actpos = 0;
		aps.mcfAPS = MCF_ON;
		base->GetMOT()->arr[i].sendAPS(&aps);
	}

	for (int i=0; i < getNumberOfMotors(); ++i) {
		for(int j=0; j < getNumberOfMotors(); ++j) {
			if(base->GetMOT()->arr[j].GetCLB()->order == i) {
				base->GetMOT()->arr[j].setCalibrated(false);
				calibrate( j, *base->GetMOT()->arr[j].GetCLB(), *base->GetMOT()->arr[j].GetSCP(), *base->GetMOT()->arr[j].GetDYL() );
				base->GetMOT()->arr[j].setCalibrated(true);
				break;
			}
		}
	}
}



void CKatana::calibrate(long idx, TMotCLB clb, TMotSCP scp, TMotDYL dyl) {

	if (!clb.enable)
		return;

	searchMechStop(idx,clb.dir,scp,dyl);
//std::cout << "setting actual position to " << base->GetMOT()->arr[idx].GetInitialParameters()->encoderOffset << " with motor command flag " << clb.mcf << std::endl;
	TMotAPS aps = { clb.mcf, base->GetMOT()->arr[idx].GetInitialParameters()->encoderOffset };
	base->GetMOT()->arr[idx].sendAPS(&aps);

	mov(idx, clb.encoderPositionAfter, true);
}


void CKatana::searchMechStop(long idx, TSearchDir dir,
                             TMotSCP _scp, TMotDYL _dyl ) {

	// with 6M Katanas, use D and S commands to set motor parameters for calibration
	if ((getNumberOfMotors() == 6) && base->GetMOT()->arr[idx].GetNmp()) {
		base->GetMOT()->arr[idx].setPwmLimits(50, 50);
		base->GetMOT()->arr[idx].setControllerParameters(_scp.kspeed_nmp, _scp.kpos_nmp, _scp.kI_nmp);
		base->GetMOT()->arr[idx].setCrashLimit(_scp.crash_limit_nmp);
		base->GetMOT()->arr[idx].setCrashLimitLinear(_scp.crash_limit_lin_nmp);
		base->GetMOT()->arr[idx].setAccelerationLimit(1);
		base->GetMOT()->arr[idx].setSpeedLimits(25, 25);
	} else {
		base->GetMOT()->arr[idx].sendSCP(&_scp);
		base->GetMOT()->arr[idx].sendDYL(&_dyl);
	}

	TMotAPS aps;
	switch (dir) {
	case DIR_POSITIVE:
		aps.actpos = -31000;		// Set the actual position equal to the
		aps.mcfAPS = MCF_FREEZE;	// extreme opposite to direction I will move
		base->GetMOT()->arr[idx].sendAPS(&aps);
		break;
	case DIR_NEGATIVE:
		aps.actpos = 31000;			// Set the actual position equal to the
		aps.mcfAPS = MCF_FREEZE;	// extreme opposite to direction I will move
		base->GetMOT()->arr[idx].sendAPS(&aps);
		break;
	};

	TMotTPS tps;
	switch (dir) {
	case DIR_POSITIVE:
		tps.tarpos = 32000;
		tps.mcfTPS = MCF_ON;
		base->GetMOT()->arr[idx].sendTPS(&tps); // Set the target position equal to
		// the extreme I am moving towards.
		break;
	case DIR_NEGATIVE:
		tps.tarpos = -32000;
		tps.mcfTPS = MCF_ON;
		base->GetMOT()->arr[idx].sendTPS(&tps);// Set the target position equal to
		// the extreme I am moving towards.

		break;
	};

	double firstSpeedSample = 100, secondSpeedSample = 100;

	KNI::Timer poll_t(POLLFREQUENCY);
	while(true) {
		poll_t.Start();
		base->GetMOT()->arr[idx].recvPVP();
		firstSpeedSample = base->GetMOT()->arr[idx].GetPVP()->vel;
//std::cout << firstSpeedSample << ", " << secondSpeedSample << std::endl;
		if( (firstSpeedSample + secondSpeedSample) == 0.0 ) {
			break; // stopper reached
		}
		secondSpeedSample = firstSpeedSample;
		poll_t.WaitUntilElapsed();
	}
	// To avoid a compensation on the motor the actual position is set to 0
	// Otherwise, as it didn't reach the target position it could attempt to go
	// on moving
//std::cout << "V=0 @: " << base->GetMOT()->arr[idx].GetPVP()->pos << std::endl;
	aps.actpos = 0;
	aps.mcfAPS = MCF_FREEZE;
//std::cout << "actual pos struct set to pos 0 and motorcommandflag 8 (hold robot)\nsending actual pos..." << std::endl;
	base->GetMOT()->arr[idx].sendAPS(&aps);
//std::cout << "sent successfully." << std::endl;

	// restore motor parameters
	if ((getNumberOfMotors() == 6) && base->GetMOT()->arr[idx].GetNmp()) {
		base->GetMOT()->arr[idx].setPwmLimits(_scp.maxppwm_nmp, _scp.maxnpwm_nmp);
		base->GetMOT()->arr[idx].setControllerParameters(_scp.kspeed_nmp, _scp.kpos_nmp, _scp.kI_nmp);
		base->GetMOT()->arr[idx].setCrashLimit(_scp.crash_limit_nmp);
		base->GetMOT()->arr[idx].setCrashLimitLinear(_scp.crash_limit_lin_nmp);
		base->GetMOT()->arr[idx].setAccelerationLimit((short) _dyl.maxaccel_nmp);
		base->GetMOT()->arr[idx].setSpeedLimits(_dyl.maxpspeed_nmp, _dyl.maxnspeed_nmp);
	}

}


void CKatana::setTolerance(long idx, int enc_tolerance) {
	base->GetMOT()->arr[idx].setTolerance(enc_tolerance);
}


bool CKatana::checkENLD(long idx, double degrees) {
	return base->GetMOT()->arr[idx].checkAngleInRange(degrees);
}


void CKatana::enableCrashLimits() {
	base->enableCrashLimits();
}


void CKatana::disableCrashLimits() {
	base->disableCrashLimits();
}


void CKatana::unBlock() {
	base->unBlock();
}


void CKatana::setCrashLimit(long idx, int limit) {
	base->setCrashLimit(idx, limit);
}

short
CKatana::getNumberOfMotors() const {
	return base->GetMOT()->cnt;
}

int
CKatana::getMotorEncoders(short number, bool refreshEncoders) const {
	if(refreshEncoders)
		base->GetMOT()->arr[number].recvPVP(); // error handling using exceptions
	return base->GetMOT()->arr[number].GetPVP()->pos;
}

std::vector<int>::iterator
CKatana::getRobotEncoders(std::vector<int>::iterator start, std::vector<int>::const_iterator end, bool refreshEncoders) const {
	if(refreshEncoders)
		base->recvMPS();
	std::vector<int>::iterator iter = start;
	for(int i = 0; i < getNumberOfMotors(); ++i) {
		if(iter == end)
			return iter;
		(*iter) = getMotorEncoders(i, false);
		++iter;
	}
	return iter;
}

std::vector<int>
CKatana::getRobotEncoders(bool refreshEncoders) const {
	std::vector<int> temp(getNumberOfMotors());
	getRobotEncoders(temp.begin(),temp.end(), refreshEncoders);
	return temp;
}

short
CKatana::getMotorVelocityLimit(short number) const {
	return base->GetMOT()->arr[number].GetDYL()->maxpspeed_nmp;
}
short
CKatana::getMotorAccelerationLimit(short number) const {
	return base->GetMOT()->arr[number].GetDYL()->maxaccel_nmp;
}

void
CKatana::setMotorVelocityLimit(short number, short velocity) {
	base->GetMOT()->arr[number].setSpeedLimit(velocity);
}

void
CKatana::setRobotVelocityLimit(short velocity) {
	for(short c = 0; c < getNumberOfMotors(); ++c) {
		base->GetMOT()->arr[c].setSpeedLimit( velocity );
	}
}

void
CKatana::setMotorAccelerationLimit(short number, short acceleration) {
	base->GetMOT()->arr[number].setAccelerationLimit(acceleration);
}

void
CKatana::setRobotAccelerationLimit(short acceleration) {
	for(short c = 0; c < getNumberOfMotors(); ++c) {
		base->GetMOT()->arr[c].setAccelerationLimit(acceleration);
	}
}

void
CKatana::moveMotorByEnc(short number, int encoders, bool waitUntilReached, int waitTimeout) {
	if(encoders >= 0) {
		inc(number, encoders, waitUntilReached, waitTimeout);
	} else {
		dec(number, abs(encoders), waitUntilReached, 100, waitTimeout);
	}
}

void
CKatana::moveMotorBy(short number, double radianAngle, bool waitUntilReached, int waitTimeout) {
	int encoders = static_cast<int>(radianAngle*static_cast<double>(base->GetMOT()->arr[number].GetInitialParameters()->encodersPerCycle)/(2*M_PI));
	if(radianAngle >= 0) {
		inc(number, encoders, waitUntilReached, waitTimeout)
		;
	} else {
		dec(number, abs(encoders), waitUntilReached, 100, waitTimeout);
	}
}

void
CKatana::moveMotorToEnc(short number, int encoders, bool waitUntilReached, int encTolerance, int waitTimeout) {
	mov(number, encoders, waitUntilReached, encTolerance, waitTimeout);
}

void
CKatana::moveMotorTo(short number, double radianAngle, bool waitUntilReached, int waitTimeout) {
	int encoders = KNI_MHF::rad2enc( radianAngle,
	                                 base->GetMOT()->arr[number].GetInitialParameters()->angleOffset,
	                                 base->GetMOT()->arr[number].GetInitialParameters()->encodersPerCycle,
	                                 base->GetMOT()->arr[number].GetInitialParameters()->encoderOffset,
	                                 base->GetMOT()->arr[number].GetInitialParameters()->rotationDirection);
	mov(number, encoders, waitUntilReached, 100, waitTimeout);
}

void
CKatana::waitForMotor( short number, int encoders, int encTolerance, short mode, int waitTimeout){
	base->GetMOT()->arr[number].waitForMotor(encoders,encTolerance,	mode, waitTimeout);
}

void
CKatana::moveRobotToEnc(std::vector<int>::const_iterator start, std::vector<int>::const_iterator end, bool waitUntilReached, int encTolerance, int waitTimeout) {

	//         // We'll do that some other time. We need to store the velocity twice for that
	//         for(unsigned int i = 0; i < getNumberOfMotors(); ++i) {
	//             distance[i] = std::abs(act_pos[i] - solution[i]);
	//         }
	//         int maxDistNr = std::distance(distance.begin(), std::max_element(distance.begin(), distance.end()));

	int i = 0;
	std::vector<int>::const_iterator iter = start;
	while( (iter != end) && (i < getNumberOfMotors()) ) {
		//             if(i != maxDistNr) {
		//                 mot->arr[i].setSpeedLimit(distance[i]/(distance[maxDistNr]/mot->arr[maxDistNr].GetDYL()->maxpspeed_nmp));
		//             }
		mov(i, *iter, false, encTolerance, waitTimeout);
		++i;
		++iter;
	}

	// If wait is true, check if the target position is reached
	if(!waitUntilReached)
		return;

	const TKatMOT* mot = base->GetMOT();
	bool pos_reached;
	KNI::Timer t(waitTimeout), poll_t(POLLFREQUENCY);
	t.Start();
	while (true) {
		if (t.Elapsed()) {
			std::ofstream logfile;
			logfile.open("MotorTimeoutException.log", std::ios_base::app);
			logfile << "MOTOR TIMEOUT EXCEPTION\nTimeout period elapsed was " << waitTimeout << "ms\n";
			int idx;
			for (idx=0; idx<getNumberOfMotors(); idx++) {
				std::cout << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
				logfile << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
			}
			std::cout << "Motors not reached target position:";
			logfile << "Motors not reached target position (less than 100 enc difference):";
			for (idx=0; idx<getNumberOfMotors(); idx++) {
				if (std::abs(mot->arr[idx].GetTPS()->tarpos - mot->arr[idx].GetPVP()->pos) >= 100) {
					std::cout << " " << idx+1;
					logfile << " " << idx+1;
				}
			}
			std::cout << "\n";
			logfile << "\n\n\n";
			logfile.close();
			throw MotorTimeoutException();
		}
		pos_reached = true;
		poll_t.Start();
		base->recvMPS(); // get position for all motors
		base->recvGMS(); // get status flags for all motors
		for (int idx=0; idx<getNumberOfMotors(); idx++) {
			if (mot->arr[idx].GetPVP()->msf == 40)
				throw MotorCrashException();
			pos_reached &= std::abs(mot->arr[idx].GetTPS()->tarpos - mot->arr[idx].GetPVP()->pos) < 100;
		}
		if (pos_reached)
			break;
		poll_t.WaitUntilElapsed();
	}
}

void
CKatana::moveRobotToEnc(std::vector<int> encoders, bool waitUntilReached, int encTolerance, int waitTimeout) {
	moveRobotToEnc(encoders.begin(), encoders.end(), waitUntilReached, encTolerance, waitTimeout);
}

void
CKatana::moveRobotToEnc4D(std::vector<int> target, int velocity, int acceleration, int encTolerance){

	int n, maxDistance = 0;
	short numberOfMotors = getNumberOfMotors();
    std::vector<int> diffMot,speed,oldSpeed;

	//Find the maximun difference between actual and target position for each motor
	for (n=0;n<numberOfMotors;n++){
		diffMot.push_back(std::abs(getMotorEncoders(n,true)-target.at(n)));
		maxDistance=max(diffMot.at(n),maxDistance);
	}

	//Save the old speeds and calculate the new speeds
	for (n=0;n<numberOfMotors;n++){
	     oldSpeed.push_back(getMotorVelocityLimit(n));
	     speed.push_back(max(static_cast<int>((static_cast<double>(diffMot.at(n))/maxDistance) * velocity),10));
	     setMotorVelocityLimit(n,speed.at(n));
	     setMotorAccelerationLimit(n,acceleration);
	}

	//Move each motor to the target position
	for (n=0;n<numberOfMotors;n++){
		moveMotorToEnc(n,target.at(n));
	}

	//Wait until the target position for all motors with the encTolerance is reached
	for (n=0;n<numberOfMotors;n++){
		waitForMotor(n,target.at(n),encTolerance);
	}

	//Restore the speeds
	for (n=0;n<numberOfMotors;n++){
		setMotorVelocityLimit(n,oldSpeed.at(n));
	}
}

void
CKatana::openGripper(bool waitUntilReached, int waitTimeout) {
	if(!_gripperIsPresent)
		return;
	moveMotorToEnc( getNumberOfMotors()-1, _gripperOpenEncoders, waitUntilReached, waitTimeout );
}

void
CKatana::closeGripper(bool waitUntilReached, int waitTimeout) {
	if(!_gripperIsPresent)
		return;
	moveMotorToEnc( getNumberOfMotors()-1, _gripperCloseEncoders, waitUntilReached, waitTimeout );
}


void
CKatana::freezeRobot() {
	for(int i = 0; i < getNumberOfMotors(); ++i)
		freezeMotor(i);
}
void
CKatana::freezeMotor(short number) {
	base->GetMOT()->arr[number].recvPVP();
	const TMotPVP *pvp = base->GetMOT()->arr[number].GetPVP();
	TMotTPS tps = { MCF_FREEZE, pvp->pos };
	base->GetMOT()->arr[number].sendTPS(&tps);
}
void
CKatana::switchRobotOn() {
	for(int i = 0; i < getNumberOfMotors(); ++i)
		// switchMotorOn(i); // with moving flag, old version for katana 1.1
		freezeMotor(i); // switch on with freeze flag, new version, safer and for katana 1.2 too
}
void
CKatana::switchRobotOff() {
	for(int i = 0; i < getNumberOfMotors(); ++i)
		switchMotorOff(i);
}
void
CKatana::switchMotorOn(short number) {
	base->GetMOT()->arr[number].recvPVP();
	const TMotPVP *pvp = base->GetMOT()->arr[number].GetPVP();
	TMotTPS tps = { MCF_ON, pvp->pos };
	base->GetMOT()->arr[number].sendTPS(&tps);
}
void
CKatana::switchMotorOff(short number) {
	base->GetMOT()->arr[number].recvPVP();
	const TMotPVP *pvp = base->GetMOT()->arr[number].GetPVP();
	TMotTPS tps = { MCF_OFF, pvp->pos };
	base->GetMOT()->arr[number].sendTPS(&tps);
}

void
CKatana::setGripperParameters(bool isPresent, int openEncoders, int closeEncoders) {
	_gripperIsPresent     = isPresent;
	_gripperOpenEncoders  = openEncoders;
	_gripperCloseEncoders = closeEncoders;
}

void
CKatana::startSplineMovement(bool exactflag, int moreflag) {
    base->startSplineMovement(exactflag, moreflag);
}


void
CKatana::startFourSplinesMovement(bool exactflag){
	base->startFourSplinesMovement(exactflag);
}

void
CKatana::sendSplineToMotor(unsigned short number, short targetPosition, short duration, short p1, short p2, short p3, short p4) {
    base->GetMOT()->arr[number].sendSpline(targetPosition, duration, p1, p2, p3, p4);
}


void
CKatana::sendFourSplinesToMotor(unsigned short number, short targetPosition, short duration, std::vector<short>& coefficients) {
    base->GetMOT()->arr[number].sendFourSplines(targetPosition, duration, coefficients);
}


void
CKatana::sendFourSplinesToMotor(unsigned short number, short targetPosition, short duration, short p01, short p11, short p21, short p31, short p02, short p12, short p22, short p32,short p03, short p13, short p23, short p33,short p04, short p14, short p24, short p34){
	std::vector<short> coefficients;
	coefficients.push_back(p01);
	coefficients.push_back(p11);
	coefficients.push_back(p21);
	coefficients.push_back(p31);
	coefficients.push_back(p02);
	coefficients.push_back(p12);
	coefficients.push_back(p22);
	coefficients.push_back(p32);
	coefficients.push_back(p03);
	coefficients.push_back(p13);
	coefficients.push_back(p23);
	coefficients.push_back(p33);
	coefficients.push_back(p04);
	coefficients.push_back(p14);
	coefficients.push_back(p24);
	coefficients.push_back(p34);

	base->GetMOT()->arr[number].sendFourSplines(targetPosition, duration, coefficients);

}


