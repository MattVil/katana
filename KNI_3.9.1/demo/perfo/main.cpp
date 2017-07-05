/***********************************************************************************

	---------------------------------------------------------------------------
	./perfo
	---------------------------------------------------------------------------

	Analyzing the performance of the robot's commands.

	(Linux) Compilation:	g++ main.cpp perfo.cpp -c -Wall
	(Linux) Linkage:	g++ main.o perfo.o libKNIBase.a -Wall -o perfo
	(Linux) Execution:	./perfo <configfile>

	---------------------------------------------------------------------------

***********************************************************************************/

#include "KNI/cdlCOM.h"	//for serial device: TCdlCOMDesc, CCdlCOM
#include "KNI/cplSerial.h"	//for serial-zero protocol: CCplSerialZero
#include "KNI/kmlBase.h"	//for robot: CKatBase, CMotBase, CSctBase
#include "KNI/kmlExt.h"	// extended katana features
#include <iostream>		//for messages: printf()
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************************/
#include "perfo.h"	//for performance checking..
/**********************************************************************************/

#ifdef WIN32
	#define COMPORT 1
#else //LINUX
	#define COMPORT 0
#endif

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("------------------------\n");
		printf("error: define *.cfg file\n");
		printf("------------------------\n");
		return 0;
	}

	printf("-------------------\n");
	printf("Hello Katana World!\n");
	printf("-------------------\n");

	//------------------------------------------------------------------------//
	//open device: a serial port is opened in that case
	//------------------------------------------------------------------------//

	TCdlCOMDesc ccd = { COMPORT, 57600, 8, 'N', 1, 100, 0};	//COM description
	CCdlCOM* device = new CCdlCOM(ccd);			//class creation &
	
	printf("success: open device\n");
	

	//------------------------------------------------------------------------//
	//init protocol: a Serial-CRC protocol is initiated in that case
	//------------------------------------------------------------------------//

	CCplSerialCRC*  protocol = new CCplSerialCRC();		//class creation
	protocol->init(device);
	printf("success: init protocol\n");

	//------------------------------------------------------------------------//
	//init robot: with the data available on the .cfg file
	//------------------------------------------------------------------------//

	CKatana* katana = new CKatana();					//create katana class
	katana->create(argv[1],protocol);

	printf("-------------------------------------------\n");
	printf("success: katana initiated\n");
	printf("-------------------------------------------\n");


	/***************************************************************************

		Here you can perform now further access to the robot, if the
		connection was succsessfully done.

	*///----------------------------------------------------------------------//

	printf("--------------------------------------------------------------\n");
	printf("Remarks: During this test the motors are not in move; but this\n");
	printf("test is a good way to analyse, if something is wrong with the\n");
	printf("robot or not! Every command is tested systematically and the\n");
	printf("response time and return values are give back.\n");
	printf("--------------------------------------------------------------\n");
	printf("Enter communication tries (e.g. 100): "); scanf("%d",&maxCnt);
	printf("--------------------------------------------------------------\n");
	
	testKat(katana->GetBase());		// test general katana methods

	for (int i=0; i<katana->GetBase()->GetMOT()->cnt; i++) { 
		testMot(katana->GetBase(),i);	// test motor methods
	};

	testSct(katana->GetBase(),0);	// test sensor methods

	//----------------------------------------------------------------------//

	/*
	--------------------------------------------------------------------------*/

	delete protocol;	//delete previously created protocol class
	delete device;		//delete previously created device class
	delete katana;		//delete previously created katana class

	//------------------------------------------------------------------------//

	printf("-------------------\n");
	printf("Byeee Katana World!\n");
	printf("-------------------\n");
	return 0;
}
