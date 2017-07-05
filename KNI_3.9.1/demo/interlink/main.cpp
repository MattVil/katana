/***********************************************************************************

	---------------------------------------------------------------------------
	./interlink
	---------------------------------------------------------------------------

	This small program initates a link between the Katana robot and the first
	COM port (COM port enumaration can start differently between different OS;
	this file was run under Linux and there the first COM port has the number
	0; under Win32 the number would be 1!).
	After the initiation a connection check will be performed and the user will
	get the result; this program should be a base for further programs, which
	are using the libKNIBase library to control the Katana robot.

	(Linux) Compilation:	g++ main.cpp -c -Wall
	(Linux) Linkage:	g++ main.o libKNIBase.a -Wall -o interlink
	(Linux) Execution:	./interlink

	---------------------------------------------------------------------------

***********************************************************************************/

#include "kniBase.h"
#include <iostream>

/**********************************************************************************/

#ifdef WIN32
	#define COMPORT 1
#else //LINUX
	#define COMPORT 0
#endif

int main() {

	std::cout << "-------------------\n";
	std::cout << "Hello Katana World!\n";
	std::cout << "-------------------\n";

	//------------------------------------------------------------------------//
	//open device: a serial port is opened in that case
	//------------------------------------------------------------------------//

	TCdlCOMDesc ccd = { COMPORT, 57600, 8, 'N', 1, 300, 0};	//COM description
	CCdlCOM* device = new CCdlCOM(ccd);			//class creation &
	
	std::cout << "-------------------------------------------\n";
	std::cout << "success: device open\n";
	std::cout << "-------------------------------------------\n";


	//------------------------------------------------------------------------//
	//init protocol: a Serial-CRC protocol is initiated in that case
	//------------------------------------------------------------------------//

	//CCplSerialZero* protocol = new CCplSerialZero();	//class creation
	CCplSerialCRC*  protocol = new CCplSerialCRC();		//class creation
	protocol->init(device);
	std::cout << "-------------------------------------------\n";
	std::cout << "success: protocol initiated\n";
	std::cout << "-------------------------------------------\n";
	

	//------------------------------------------------------------------------//
	//init robot: a katana with 5 motors and 1 sensor controller is initiated
	//	the master's jumper addres is		24
	//	the slave ID's of the motors are	1,2,3,4 or 5
	//	the sensor ctrl's ID is			15
	//	the sensor ctrl's resolution is		8
	//	the count of sensors is			16
	//------------------------------------------------------------------------//

	//set general katana values
	TKatGNL   general    = {24};			//jumper address

	//set motor values
	TMotDesc  motdesc[5] = {{1}, {2}, {3}, {4}, {5}};//motor's slave ID's
	CMotBase* motarr     = new CMotBase[5];		//create motor class
	TKatMOT   katmot     = {5, motarr, motdesc};	//fill a TKatMOT structure

	//set sensor controller values
	TSctDesc  sctdesc[1] = {{15, 8, 16}};		//sctID,resol,count
	CSctBase* sctarr     = new CSctBase[1];		//create sensor-ctrl class
	TKatSCT   katsct     = {1, sctarr, sctdesc};	//fill TKatSCT structure
	TKatEFF*   eff		 = new TKatEFF;	//fill TKatEFF structure

	//initiate the 'katana' class
	CKatBase* katana = new CKatBase();		//create katana class
	katana->init(general,katmot,katsct,*eff, protocol);
	std::cout << "-------------------------------------------\n";
	std::cout << "success: katana initiated\n";
	std::cout << "-------------------------------------------\n";

	/***************************************************************************

		Here you can perform now further access to the robot, if the
		connection was succsessfully done.

		The simplest command would be the get an echo from the robot:
	*/

	katana->recvECH();
	std::cout << "ECHO succeded.\n";

	/*
	--------------------------------------------------------------------------*/

	delete katana;		//delete previously created katana class
	delete protocol;	//delete previously created protocol class
	delete device;		//delete previously created device class

	//------------------------------------------------------------------------//

	std::cout << "-------------------\n";
	std::cout << "Byeee Katana World!\n";
	std::cout << "-------------------\n";
	return 0;
}
