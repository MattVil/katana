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


#include "KNI_InvKin/ikBase.h"
#include "KNI_InvKin/KatanaKinematics6M90G.h"
#include "KNI_InvKin/KatanaKinematics6M90T.h"
#include "KNI_InvKin/KatanaKinematics6M180.h"
#include "KNI_InvKin/KatanaKinematics5M180.h"


void CikBase::_initKinematics() {

	if( std::string(base->GetGNL()->modelName) == "Katana6M90G") {
		_kinematicsImpl.reset(new KNI::KatanaKinematics6M90G);
	} else if(std::string(base->GetGNL()->modelName) == "Katana6M90T") {
		_kinematicsImpl.reset(new KNI::KatanaKinematics6M90T);
	} else if(std::string(base->GetGNL()->modelName) == "Katana6M180") {
		_kinematicsImpl.reset(new KNI::KatanaKinematics6M180);
	} else if(std::string(base->GetGNL()->modelName) == "Katana5M180") {
		_kinematicsImpl.reset(new KNI::KatanaKinematics5M180);
	} else {
		return;
	}

	const TKatEFF* eff = base->GetEFF();
	const TKatMOT* mot = base->GetMOT();

	KNI::KatanaKinematics::metrics length;
	for(int i = 0; i < getNumberOfMotors()-2; ++i) {
		length.push_back( eff->arr_segment[i] );
	}

	KNI::KinematicParameters joint;
	KNI::KatanaKinematics::parameter_container parameters;
	for(int i = 0; i < getNumberOfMotors(); ++i) {
		joint.epc         = mot->arr[i].GetInitialParameters()->encodersPerCycle;
		joint.encOffset   = mot->arr[i].GetInitialParameters()->encoderOffset;
		joint.angleOffset = mot->arr[i].GetInitialParameters()->angleOffset;
		joint.angleStop   = mot->arr[i].GetInitialParameters()->angleStop;
		joint.rotDir      = mot->arr[i].GetInitialParameters()->rotationDirection;
		parameters.push_back(joint);
	}

	_kinematicsImpl->init(length, parameters);

	_kinematicsIsInitialized = true;
}

void CikBase::DKApos(double* position) {
	getCoordinates(position[0], position[1], position[2], position[3], position[4], position[5]);
}

void CikBase::IKCalculate(double X, double Y, double Z, double phi, double theta, double psi, std::vector<int>::iterator solution_iter) {

	if(!_kinematicsIsInitialized)
		_initKinematics();

	std::vector<double> pose(6);
	pose[0] = X;
	pose[1] = Y;
	pose[2] = Z;
	pose[3] = phi;
	pose[4] = theta;
	pose[5] = psi;

	std::vector<int> actualPosition;
	base->recvMPS();
	for(int c = 0; c < getNumberOfMotors(); ++c) {
		actualPosition.push_back(getMotorEncoders(c, false));
	}

	_kinematicsImpl->IK(solution_iter, pose, actualPosition);

}

void CikBase::IKCalculate(double X, double Y, double Z, double phi, double theta, double psi, std::vector<int>::iterator solution_iter, const std::vector<int>& actualPosition) {

	if(!_kinematicsIsInitialized)
		_initKinematics();

	std::vector<double> pose(6);
	pose[0] = X;
	pose[1] = Y;
	pose[2] = Z;
	pose[3] = phi;
	pose[4] = theta;
	pose[5] = psi;

	_kinematicsImpl->IK(solution_iter, pose, actualPosition);

}

void CikBase::IKGoto(double X, double Y, double Z, double Al, double Be, double Ga,  bool wait, int tolerance, long timeout) {

	if(!_kinematicsIsInitialized)
		_initKinematics();

	const TKatMOT* mot = base->GetMOT();

	std::vector<int> solution(getNumberOfMotors());
	// fills act_pos[] with the current position in degree units
	std::vector<int> act_pos(getNumberOfMotors());
	std::vector<int> distance(getNumberOfMotors());

	base->recvMPS();
	for (int idx=0; idx<getNumberOfMotors(); ++idx) {
		act_pos[idx] = mot->arr[idx].GetPVP()->pos;
	}

	IKCalculate( X, Y, Z, Al, Be, Ga, solution.begin(), act_pos );
	moveRobotToEnc( solution.begin(), solution.end(), wait, timeout);

}


void CikBase::getCoordinates(double& x, double& y, double& z, double& phi, double& theta, double& psi, bool refreshEncoders) {

	if(!_kinematicsIsInitialized)
		_initKinematics();

	std::vector<int> current_encoders(getNumberOfMotors());
	std::vector<double> pose(6);

	if(refreshEncoders)
		base->recvMPS();
	for (int i=0; i<getNumberOfMotors(); i++) {
		current_encoders[i] = base->GetMOT()->arr[i].GetPVP()->pos;
	}

	_kinematicsImpl->DK(pose, current_encoders);

	x = pose[0];
	y = pose[1];
	z = pose[2];
	phi = pose[3];
	theta = pose[4];
	psi = pose[5];
}

void CikBase::moveRobotTo(double x, double y, double z, double phi, double theta, double psi, const bool waitUntilReached, const int waitTimeout) {
	IKGoto(x, y, z, phi, theta, psi, waitUntilReached, 100, waitTimeout);
}

void CikBase::moveRobotTo(std::vector<double> coordinates, const bool waitUntilReached, const int waitTimeout) {
	IKGoto(coordinates.at(0), coordinates.at(1), coordinates.at(2), coordinates.at(3), coordinates.at(4), coordinates.at(5), waitUntilReached, 100, waitTimeout);
}
