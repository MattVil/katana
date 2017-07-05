

#include "kniBase.h"
#include <iostream>
#ifdef WIN32
#include <conio.h> //ONLY WIN32 COMPATIBLE!!
#endif
#include <time.h>

//------------------------------------------------------------------------//


int main(int argc, char *argv[]) {

	if (argc != 2) {
		std::cout << "---------------------------------\n";
		std::cout << "usage: sensor SERIALPORT\n";
		std::cout << "---------------------------------\n";
		return 0;
	}

	int port = atoi(argv[1]);

	std::cout << "-----------------------\n";
	std::cout << "SENSOR DEMO STARTED\n";
	std::cout << "-----------------------\n";

	//------------------------------------------------------------------------//
	//open device: a serial port is opened in that case
	//------------------------------------------------------------------------//

	TCdlCOMDesc ccd = {port, 57600, 8, 'N', 1, 300, 0};	//COM description
	CCdlCOM* device = new CCdlCOM(ccd);			//class creation &

        std::cout << "-------------------------------------------\n";
        std::cout << "success: open device\n";
        std::cout << "-------------------------------------------\n";
	

	//------------------------------------------------------------------------//
	//init protocol: a Serial-CRC protocol is initiated in that case
	//------------------------------------------------------------------------//

	//CCplSerialZero* protocol = new CCplSerialZero();	//class creation
	CCplSerialCRC*  protocol = new CCplSerialCRC();		//class creation
	protocol->init(device);
        std::cout << "-------------------------------------------\n";
        std::cout << "success: init protocol\n";
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

	//set end effector values
	TKatEFF eff = {{ 0.0, 190.2, 139.1, 308.0 }};


	//initiate the 'katana' class
	CKatBase* base = new CKatBase();		//create katana class
	base->init(general,katmot,katsct,eff,protocol);
        std::cout << "-------------------------------------------\n";
        std::cout << "success: init katana\n";
        std::cout << "-------------------------------------------\n";


	/****************************************************************************/

	std::cout << "This program will get sensor data till you press a key..\n\n";
	CSctBase* sensctrl	= &base->GetSCT()->arr[0];		//get pointer to controller
	const TSctDAT* data	= sensctrl->GetDAT();			//get pointer to data

	bool* change = new bool[data->cnt];
	byte* lastarr = new byte[data->cnt];
	sensctrl->recvDAT();								//update sensor data
	for (int k=0; k<data->cnt; k++) {					//init stuff
		change[k] = false;
		lastarr[k] = (byte) data->arr[k];
	}
#ifdef WIN32
	while (!_kbhit()) { //_kbhit(): ONLY WIN32 COMPATIBLE
#else
	while(true) { // means: you have to stop with ctrl-c
#endif
		clock_t t = clock();							//init timer
		sensctrl->recvDAT();							//update sensor data
		for (int i=0; i<data->cnt; i++) {
			std::cout.width(5);
			std::cout << data->arr[i] << " ";				//printout data	
		} std::cout << "\n";
		while (clock() - t < 25) {}						//wait 25 millisec

		for (int j=0; j<data->cnt; j++) {
			change[j] |= (data->arr[j] != lastarr[j]);
			lastarr[j] = (byte) data->arr[j];
		}
	}

	for (int l=0; l<data->cnt; l++) {
		std::cout << "--------------------------------------------------------------------\n";
		std::cout << l << ": ";
		change[l] ? std::cout << "reacting: everything should be well" : std::cout << "no activity detected: probably a hardware error";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------------------\n";
	} while(true) {}

	//delete[] change;
	//delete[] lastarr;

	/****************************************************************************/


	delete base;		//delete previously created katana class
	delete protocol;	//delete previously created protocol class
	delete device;		//delete previously created device class

	//------------------------------------------------------------------------//

	std::cout << "-------------------\n";
	std::cout << "Byeee Katana World!\n";
	std::cout << "-------------------\n";
	return 0;
}
