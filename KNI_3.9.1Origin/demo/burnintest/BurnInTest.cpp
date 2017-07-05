/* * * * * * * *
 * Burn-In-Test using KNI with sockets
 * Author: Jonas Haller <jonas.haller@neuronics.ch>
 * (c) Neuronics AG   2007
 */

// maximum velocity of test movements
#define VELOCITY 120
// tolerance of position in encoders
#define TOLERANCE 100
// timeout for a movement in ms (max. move duration is approx. 4 seconds, so 10 seconds is OK)
#define MOVETIMEOUT 10000
// number of tries if a move timeout occurs during a test movement
#define TRIESONMOVETIMEOUT 5
// time between polls to check if mechanical stopper reached in ms
#define POLLFREQUENCY 300
// maximum number of crashs (all axis together)
#define MAXCOLLISIONS 1000
// maximum number of crashs on each axis
#define MAXCOLLISIONSONAXIS 1000


#include "kniBase.h"
#include "KNI/kmlMotBase.h"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <memory>
#include <vector>
#include <fstream>
#include <string.h>

#include "keyboard.h"

#include <algorithm>
#include <iterator>

const int INHIBITTIME = 200000;

struct Tpos {
	static std::vector<int> w,x,y,z;
	static const int wArr[], xArr[], yArr[], zArr[];
};
//Katana object and global variables
std::auto_ptr<CLMBase> katana;
int numberOfMotors;
int serialNr;
int totalCrashs = 0;
int motorCrashs[6] = {0, 0, 0, 0, 0, 0};
std::ofstream logfile;

//positions, hard-coded.
//6M90T also works for 6M180 and 6M90G
const int Tpos::wArr[] = {19200, -22150, -25953, 14410, 19410, 25000};
const int Tpos::xArr[] = {6390, 1680, -14081, 27216, 6613, 12000};
const int Tpos::yArr[] = {-6400, -22150, -2209, 14410, -6189, 25000};
const int Tpos::zArr[] = {6390, 1680, -2209, 1614, 6613, 12000};

std::vector<int> Tpos::w(wArr, wArr + sizeof(wArr)/sizeof(*wArr));
std::vector<int> Tpos::x(xArr, xArr + sizeof(xArr)/sizeof(*xArr));
std::vector<int> Tpos::y(yArr, yArr + sizeof(yArr)/sizeof(*yArr));
std::vector<int> Tpos::z(zArr, zArr + sizeof(zArr)/sizeof(*zArr));
std::vector<int> homeposition;

// init timestructs
time_t rawtime;
struct tm * timeinfo;
char timestring[] = "dd.mm.yyyy-hh:mm:ss";

char* timestamp() {
	time(&rawtime);
	// NOTE: hour offset hack
	rawtime -= 3600;
	timeinfo = localtime(&rawtime);
	timestring[0] = (char) (timeinfo->tm_mday / 10 + 48);
	timestring[1] = (char) (timeinfo->tm_mday % 10 + 48);
	timestring[3] = (char) ((timeinfo->tm_mon + 1) / 10 + 48);
	timestring[4] = (char) ((timeinfo->tm_mon + 1) % 10 + 48);
	timestring[6] = (char) ((timeinfo->tm_year + 1900) / 1000 + 48);
	timestring[7] = (char) (((timeinfo->tm_year + 1900) / 100) % 10 + 48);
	timestring[8] = (char) (((timeinfo->tm_year + 1900) / 10) % 10 + 48);
	timestring[9] = (char) ((timeinfo->tm_year + 1900) % 10 + 48);
	timestring[11] = (char) ((timeinfo->tm_hour + 1) / 10 + 48);
	timestring[12] = (char) ((timeinfo->tm_hour + 1) % 10 + 48);
	timestring[14] = (char) ((timeinfo->tm_min + 1) / 10 + 48);
	timestring[15] = (char) ((timeinfo->tm_min + 1) % 10 + 48);
	timestring[17] = (char) ((timeinfo->tm_sec + 1) / 10 + 48);
	timestring[18] = (char) ((timeinfo->tm_sec + 1) % 10 + 48);
	return &timestring[0];
}

void openlogfile(char* aSN) {
	char logfilename[] = "burn-in-SNXXXX_0001.log";
	strncpy(&logfilename[10], aSN, 4);
	FILE * file = fopen(logfilename, "r");
	int i = 1;
	while (file != NULL) {
		fclose(file);
		file = NULL;
		i++;
		if (i > 9999) {
			std::cout << "all 9999 logfile numbers for this katana taken!\nexiting program.\n";
			exit(-1);
		}
		logfilename[15] = (char) ((i / 1000) % 10 + 48);
		logfilename[16] = (char) ((i / 100) % 10 + 48);
		logfilename[17] = (char) ((i / 10) % 10 + 48);
		logfilename[18] = (char) (i % 10 + 48);
		file = fopen(logfilename, "r");
	}
	std::cout << "\nopening log file (" << logfilename << ")...\n";
	logfile.open(logfilename, std::ios_base::app);
	return;
}

bool readencoders(std::vector<int>& aEncCalib, std::vector<int>& aEncOpposit) {
	bool ok = true;
	bool loop = true;
	int input;
	bool isOff = false;
	std::vector<int> encoders(numberOfMotors, 0);
	int storedencoders = 0;
	aEncCalib.reserve(numberOfMotors);
	aEncOpposit.reserve(numberOfMotors);
	while (loop) {
		input = _getch();
		try {
			switch (input) {
				case 3:
				case 4:
					case 27: //VK_ESCAPE
						std::cout << "test cancelled.\n";
						loop = false;
						ok = false;
						break;
						case 'o': //VK_O (motors off/on)
							if(isOff) {
								katana->switchRobotOn();
								isOff = false;
							} else {
								katana->switchRobotOff();
								isOff = true;
							}
							break;
							case 'e': //VK_E (read encoder values)
								katana->getRobotEncoders(encoders.begin(), encoders.end());
								std::cout << "\nencoder values:";
								for (std::vector<int>::iterator it= encoders.begin(); it != encoders.end(); ++it) {
									std::cout << " " << *it;
								}
								std::cout << "\n";
                // if less than the required two samples stored
								if (storedencoders < 2) {
									std::cout << "store these encoder values? (y/n)\n";
									input = _getch();
									if (input == 'y') {
										logfile << timestamp() << ";MS";
										for (std::vector<int>::iterator it= encoders.begin(); it != encoders.end(); ++it) {
										logfile << ";" << *it;
										}
										logfile << "\n";
										storedencoders++;
										if (storedencoders == 1) {
										for (std::vector<int>::iterator it= encoders.begin(); it != encoders.end(); ++it) {
										aEncCalib.push_back(*it);
										}
										}
										if (storedencoders == 2) {
										for (std::vector<int>::iterator it= encoders.begin(); it != encoders.end(); ++it) {
										aEncOpposit.push_back(*it);
										}
										}
										std::cout << "values stored.\n";
									} else {
										std::cout << "values omitted.\n";
									}
								}
								break;
								case 'f': //VK_F (finished)
									if (storedencoders != 2) {
										std::cout << "two encoders needed (calibration and opposit), only " <<
										storedencoders << " stored!\ndo you really want to quit? (y/n)\n";
										input = _getch();
										if (input == 'y') {
										std::cout << "test cancelled.\n";
										loop = false;
										ok = false;
										} else {
										std::cout << "please read further encoders...\n";
										}
									} else {
										loop = false;
									}
									break;
									default: //Error message
										std::cout << "\n'" << input << "' is not a valid command.\n" << std::endl;
										break;
			}
		} catch (Exception &e) {
			std::cout << "\nERROR: " << e.message() << std::endl;
		}
	}
	return ok;
}

bool testMoves() {
	char state = 0;
	char quitchar;
	bool ok = true;
	bool failed = false;
	bool loop = true;

	while (loop) {
		switch (state) {
			case 0:
				try {
					katana->moveRobotToEnc(Tpos::w, true, TOLERANCE, MOVETIMEOUT);
				} catch (MotorCrashException &ex) {
					failed = true;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile << "\n\nMOTOR CRASH EXCEPTION\n\nMotors in collieded state:";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR CRASH EXECEPTION\n\nMotors in collieded state:";
					for (int idx=0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						if (mot->arr[idx].GetPVP()->msf == 40) {
							totalCrashs++;
							motorCrashs[idx]++;
							logfile << " " << idx + 1;
							std::cout << " " << idx + 1;
							if (totalCrashs >= MAXCOLLISIONS || motorCrashs[idx] >= MAXCOLLISIONSONAXIS) {
								if(totalCrashs >= MAXCOLLISIONS) {
									logfile << "\n\nMaximum of crashs over all axis reached, test aborted.";
									std::cout << "\n\nMaximum of crashs over all axis reached, test aborted.";
								} else {
									logfile << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
									std::cout << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
								}
								ok = false;
								loop = false;
							} else {
								katana->unBlock();
							}
						}
					}
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					std::cout << "\n\n===================================================================================\n\n";
				} catch (MotorTimeoutException &ex) {
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile <<"\n\nMOTOR TIMEOUT EXCEPTION\nTimeout period elapsed was " << MOVETIMEOUT << "ms\n\n";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR TIMEOUT EXCEPTION\n\n";
					int idx;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					for (idx = 0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						std::cout << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
						logfile << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
					}
					std::cout << "Motors not reached target position:";
					logfile << "Motors not reached target position (less than 100 enc difference):";
					for (idx=0; idx < numberOfMotors; idx++) {
						if (std::abs(mot->arr[idx].GetTPS()->tarpos - mot->arr[idx].GetPVP()->pos) >= 100) {
							std::cout << " " << idx+1;
							logfile << " " << idx+1;
						}
					}
					std::cout << "\n\n";
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					ok = false;
					loop = false;	
				}
				if(failed) {
					failed = false;
				} else {
					state = 1;
				}
				if (kbhit() == true) {
					quitchar = readch();
					if (quitchar == 27) {
						ok = false;
					}
				}
				usleep(INHIBITTIME);
				break;
			case 1:
				try {
					katana->moveRobotToEnc(Tpos::x, true, TOLERANCE, MOVETIMEOUT);
				} catch (MotorCrashException &ex) {
					failed = true;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile << "\n\nMOTOR CRASH EXCEPTION\n\nMotors in collieded state:";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR CRASH EXECEPTION\n\nMotors in collieded state:";
					for (int idx=0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						if (mot->arr[idx].GetPVP()->msf == 40) {
							totalCrashs++;
							motorCrashs[idx]++;
							logfile << " " << idx + 1;
							std::cout << " " << idx + 1;
							if (totalCrashs >= MAXCOLLISIONS || motorCrashs[idx] >= MAXCOLLISIONSONAXIS) {
								if(totalCrashs >= MAXCOLLISIONS) {
									logfile << "\n\nMaximum of crashs over all axis reached, test aborted.";
									std::cout << "\n\nMaximum of crashs over all axis reached, test aborted.";
								} else {
									logfile << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
									std::cout << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
								}
								ok = false;
								loop = false;
							} else {
								katana->unBlock();
							}
						}
					}
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					std::cout << "\n\n===================================================================================\n\n";
				} catch (MotorTimeoutException &ex) {
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile <<"\n\nMOTOR TIMEOUT EXCEPTION\nTimeout period elapsed was " << MOVETIMEOUT << "ms\n\n";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR TIMEOUT EXCEPTION\n\n";
					int idx;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					for (idx = 0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						std::cout << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
						logfile << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
					}
					std::cout << "Motors not reached target position:";
					logfile << "Motors not reached target position (less than 100 enc difference):";
					for (idx=0; idx < numberOfMotors; idx++) {
						if (std::abs(mot->arr[idx].GetTPS()->tarpos - mot->arr[idx].GetPVP()->pos) >= 100) {
							std::cout << " " << idx+1;
							logfile << " " << idx+1;
						}
					}
					std::cout << "\n\n";
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					ok = false;
					loop = false;	
				}
				if(failed) {
					failed = false;
				} else {
					state = 2;
				}
				if (kbhit() == true) {
					quitchar = readch();
					if (quitchar == 27) {
						ok = false;
					}
				}
				usleep(INHIBITTIME);
				break;
			case 2:
				try {
					katana->moveRobotToEnc(Tpos::y, true, TOLERANCE, MOVETIMEOUT);
				} catch (MotorCrashException &ex) {
					failed = true;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile << "\n\nMOTOR CRASH EXCEPTION\n\nMotors in collieded state:";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR CRASH EXECEPTION\n\nMotors in collieded state:";
					for (int idx=0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						if (mot->arr[idx].GetPVP()->msf == 40) {
							totalCrashs++;
							motorCrashs[idx]++;
							logfile << " " << idx + 1;
							std::cout << " " << idx + 1;
							if (totalCrashs >= MAXCOLLISIONS || motorCrashs[idx] >= MAXCOLLISIONSONAXIS) {
								if(totalCrashs >= MAXCOLLISIONS) {
									logfile << "\n\nMaximum of crashs over all axis reached, test aborted.";
									std::cout << "\n\nMaximum of crashs over all axis reached, test aborted.";
								} else {
									logfile << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
									std::cout << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
								}
								ok = false;
								loop = false;
							} else {
								katana->unBlock();
							}
						}
					}
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					std::cout << "\n\n===================================================================================\n\n";
				} catch (MotorTimeoutException &ex) {
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile <<"\n\nMOTOR TIMEOUT EXCEPTION\nTimeout period elapsed was " << MOVETIMEOUT << "ms\n\n";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR TIMEOUT EXCEPTION\n\n";
					int idx;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					for (idx = 0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						std::cout << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
						logfile << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
					}
					std::cout << "Motors not reached target position:";
					logfile << "Motors not reached target position (less than 100 enc difference):";
					for (idx=0; idx < numberOfMotors; idx++) {
						if (std::abs(mot->arr[idx].GetTPS()->tarpos - mot->arr[idx].GetPVP()->pos) >= 100) {
							std::cout << " " << idx+1;
							logfile << " " << idx+1;
						}
					}
					std::cout << "\n\n";
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					ok = false;
					loop = false;	
				}
				if(failed) {
					failed = false;
				} else {
					state = 3;
				}
				if (kbhit() == true) {
					quitchar = readch();
					if (quitchar == 27) {
						ok = false;
					}
				}
				usleep(INHIBITTIME);
				break;
			case 3:
				try {
					katana->moveRobotToEnc(Tpos::z, true, TOLERANCE, MOVETIMEOUT);
				} catch (MotorCrashException &ex) {
					failed = true;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile << "\n\nMOTOR CRASH EXCEPTION\n\nMotors in collieded state:";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR CRASH EXECEPTION\n\nMotors in collieded state:";
					for (int idx=0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						if (mot->arr[idx].GetPVP()->msf == 40) {
							totalCrashs++;
							motorCrashs[idx]++;
							logfile << " " << idx + 1;
							std::cout << " " << idx + 1;
							if (totalCrashs >= MAXCOLLISIONS || motorCrashs[idx] >= MAXCOLLISIONSONAXIS) {
								if(totalCrashs >= MAXCOLLISIONS) {
									logfile << "\n\nMaximum of crashs over all axis reached, test aborted.";
									std::cout << "\n\nMaximum of crashs over all axis reached, test aborted.";
								} else {
									logfile << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
									std::cout << "\n\nMaximum of crashs on axis " << idx + 1 << " reached, test aborted.";
								}
								ok = false;
								loop = false;
							} else {
								katana->unBlock();
							}
						}
					}
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					std::cout << "\n\n===================================================================================\n\n";
				} catch (MotorTimeoutException &ex) {
					std::ofstream logfile;
					logfile.open("MotorTimeoutException.log", std::ios_base::app);
					logfile << "Robot: " << serialNr << "\n\n";
					logfile << timestamp();
					logfile <<"\n\nMOTOR TIMEOUT EXCEPTION\nTimeout period elapsed was " << MOVETIMEOUT << "ms\n\n";
					std::cout << "\n" << timestamp();
					std::cout << "\n\nMOTOR TIMEOUT EXCEPTION\n\n";
					int idx;
					const TKatMOT* mot = katana->GetBase()->GetMOT();
					for (idx = 0; idx < numberOfMotors; idx++) {
						mot->arr[idx].recvPVP();
						std::cout << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
						logfile << "Motor " << idx+1 << ":\n  status: " << mot->arr[idx].GetPVP()->msf << "\n  target position: " << mot->arr[idx].GetTPS()->tarpos << "\n  position: " << mot->arr[idx].GetPVP()->pos << "\n  velocity: " << mot->arr[idx].GetPVP()->vel << "\n";
					}
					std::cout << "Motors not reached target position:";
					logfile << "Motors not reached target position (less than 100 enc difference):";
					for (idx=0; idx < numberOfMotors; idx++) {
						if (std::abs(mot->arr[idx].GetTPS()->tarpos - mot->arr[idx].GetPVP()->pos) >= 100) {
							std::cout << " " << idx+1;
							logfile << " " << idx+1;
						}
					}
					std::cout << "\n\n";
					logfile << "\n\n===================================================================================\n\n";
					logfile.close();
					ok = false;
					loop = false;	
				}
				if(failed) {
					failed = false;
				} else {
					loop = false;
				}
				if (kbhit() == true) {
					quitchar = readch();
					if (quitchar == 27) {
						ok = false;
					}
				}
				usleep(INHIBITTIME);
				break;
		}
	}
	return ok;
}

bool measuremechstops(int* encoders) {
	bool ok = true;
	byte oldPWM, oldSpeed, oldAcceleration, tmpByte;
	CMotBase motor;
	const TMotCLB* clb;
	short direction = 1;
	TMotTPS tps;

	katana->moveRobotToEnc(homeposition, true, TOLERANCE, MOVETIMEOUT);

	for (int i = 0; i < numberOfMotors; i++) {
		motor = katana->GetBase()->GetMOT()->arr[i];
		clb = motor.GetCLB();
		switch (clb->dir) {
			case DIR_POSITIVE:
				direction = 1;
				break;
			case DIR_NEGATIVE:
				direction = -1;
				break;
		};

        // safe old limits
		motor.getParameterOrLimit(254, &oldPWM, &tmpByte, &tmpByte);
		motor.getParameterOrLimit(253, &oldSpeed, &tmpByte, &tmpByte);
		motor.getParameterOrLimit(252, &oldAcceleration, &tmpByte, &tmpByte);

        // set safe limits
		motor.setPwmLimits(50, 50);
		motor.setSpeedLimits(25, 25);

        // move to mechstops
		tps.tarpos = direction * 32000;
		tps.mcfTPS = MCF_ON;
		motor.sendTPS(&tps);

        // wait for movement to finish
		double firstSpeedSample = 100, secondSpeedSample = 100;
		KNI::Timer poll_t(POLLFREQUENCY);
		while(true) {
			poll_t.Start();
			motor.recvPVP();
			firstSpeedSample = motor.GetPVP()->vel;
			if( (firstSpeedSample + secondSpeedSample) == 0.0 ) {
				break; // stopper reached
			}
			secondSpeedSample = firstSpeedSample;
			poll_t.WaitUntilElapsed();
		}

        // finished, freeze
		tps.tarpos = 0; // ignored with freeze
		tps.mcfTPS = MCF_FREEZE;
		motor.sendTPS(&tps);

        // read encoder
		encoders[i] = katana->getMotorEncoders(i, true);

        // move back a bit
		tps.tarpos = direction * 30000;
		tps.mcfTPS = MCF_ON;
		motor.sendTPS(&tps);

        // restore old limits
		motor.setPwmLimits(oldPWM, oldPWM);
		motor.setSpeedLimits((short) oldSpeed, (short) oldSpeed);
		motor.setAccelerationLimit((short) oldAcceleration);
	}
	return ok;
}

int main(int argc, char *argv[]) {
	int repetitions;
	if (argc != 6) {
		std::cout << "----------------------------------------------------------\n";
		std::cout << "usage: BurnInTest CONFIGFILE IP_ADDR PORT KATANA_S/N HOURS\n";
		std::cout << "----------------------------------------------------------\n";
		return 0;
	}
	if (strlen(argv[4]) != 4) {
		std::cout << "Katana Serial Number has four digits!\n";
		return 0;
	}
	repetitions = atoi(argv[5]);
	repetitions = repetitions / 2 + 1;
	std::cout << "--------------------------\n";
	std::cout << "BURN-IN-TEST STARTED\n";
	std::cout << "--------------------------\n";

	std::auto_ptr<CCdlSocket> device;
	std::auto_ptr<CCplSerialCRC> protocol;

	try {
        // connect to katana
		int port = atoi(argv[3]);
		serialNr = atoi(argv[4]);
		device.reset(new CCdlSocket(argv[2], atoi(argv[3])));
		std::cout << "-------------------------------------------\n";
		std::cout << "success:  socket to " << argv[2] << ":" << port << " open\n";
		std::cout << "-------------------------------------------\n";

		protocol.reset(new CCplSerialCRC());
		protocol->init(device.get());
		std::cout << "-------------------------------------------\n";
		std::cout << "success: protocol initiated\n";
		std::cout << "-------------------------------------------\n";

		katana.reset(new CLMBase());
		katana->create(argv[1], protocol.get());
		std::cout << "-------------------------------------------\n";
		std::cout << "success: katana initiated\n";
		std::cout << "-------------------------------------------\n";

		numberOfMotors = katana->getNumberOfMotors();

	} catch(Exception &e) {
		std::cout << "ERROR: " << e.message() << std::endl;
		return -1;
	}

	try {
        // open logfile
		std::cout << "\nPlease enter the Katana description, e.g. 'KatHD400s-6M90-M6/G':\n";
		std::string description;
		std::cin >> description;
		openlogfile(argv[4]);
		logfile << timestamp() << ";Start;" << timestamp() << "\n";
		int testtotal = 0;
		int test2total = 0;
		struct timeval starttime;
		gettimeofday(&starttime, 0);
		logfile << timestamp() << ";Desc;" << description << "\n";
		logfile << timestamp() << ";SN;" << argv[4] << "\n";
		logfile << timestamp() << ";Angle";
		for (int i = 0; i < numberOfMotors; i++) {
			logfile << ";" << katana->GetBase()->GetMOT()->arr[i].GetInitialParameters()->angleOffset;
		}
		logfile << "\n";
		logfile << timestamp() << ";EPC";
		for (int i = 0; i < numberOfMotors; i++) {
			logfile << ";" << katana->GetBase()->GetMOT()->arr[i].GetInitialParameters()->encodersPerCycle;
		}
		logfile << "\n";
		logfile << timestamp() << ";Length";
		for (int i = 0; i < numberOfMotors-2; i++) {
			logfile << ";" << katana->GetBase()->GetEFF()->arr_segment[i];
		}
		logfile << "\n";
		logfile.flush();
		std::cout << "done.\n";

        // calibrate
		std::cout << "\nSTAGE 1\ncalibrating katana...\n";
		katana->calibrate();
		std::vector<int> homeencoders(numberOfMotors, 0);
		katana->getRobotEncoders(homeencoders.begin(), homeencoders.end());
		std::cout << "store home position:";
		homeposition.reserve(numberOfMotors);
		for (std::vector<int>::iterator it= homeencoders.begin(); it != homeencoders.end(); ++it) {
			homeposition.push_back(*it);
			std::cout << " " << *it;
		}
		std::cout << "\ndone.\n";

        // read encoders before test
		std::cout << "\nSTAGE 2\nreading encoder before burn-in-test:\n- switch "
				<< "robot off with 'o'-key\n- move robot to stop positions reached"
				<< " during calibration\n- read encoders with 'e'-key\n- move "
				<< "every axis to opposite stop position\n- read encoders with "
				<< "'e'-key\n- move robot back to home position\n- press 'f'-key "
				<< "to finish this stage and start the test movements\n";
		std::vector<int> enccalibbefore;
		std::vector<int> encoppositbefore;
		if (!readencoders(enccalibbefore, encoppositbefore)) {
			return -1;
		}
		logfile.flush();

        // run test
		std::cout << "\nSTAGE 3\nburn-in-test:\n";
		std::cout << "setting maximum velocity for all motors to " << VELOCITY << "...\n";
		katana->setRobotVelocityLimit(VELOCITY);
		std::cout << "done.\n";
		int mot6calibstop = enccalibbefore[numberOfMotors-1];
		int mot6oppositstop = encoppositbefore[numberOfMotors-1];
		int mot6pos1, mot6pos2;
		if ((mot6calibstop - mot6oppositstop) > 2000) {
			mot6pos1 = mot6calibstop - 1000;
			mot6pos2 = mot6oppositstop + 1000;
		} else {
			mot6pos1 = (mot6calibstop + mot6oppositstop) / 2;
			mot6pos2 = mot6pos1;
		}
		std::cout << "set test range for motor 6 to [" << mot6pos1 << ", " <<
				mot6pos2 << "] ...\n";
		Tpos::w.pop_back();
		Tpos::w.push_back(mot6pos1);
		Tpos::x.pop_back();
		Tpos::x.push_back(mot6pos2);
		Tpos::y.pop_back();
		Tpos::y.push_back(mot6pos1);
		Tpos::z.pop_back();
		Tpos::z.push_back(mot6pos2);
		std::cout << "done.\n";
		std::cout << "starting test moves...\n";
		std::cout << "   press 'Esc' key to abort test movement\n";
		init_keyboard();
		int encoders[numberOfMotors];
		int i, j, k, l;
		if (measuremechstops(encoders)) {
			logfile << timestamp() << ";MC";
			for (l = 0; l < numberOfMotors; l++) {
				logfile << ";" << encoders[l];
			}
			logfile << "\n";
			logfile.flush();
		} else {
			i = j = k = 120;
			std::cout << "Exception.\nContinuing with stage 4.\n";
		}
        // repetitions (total ca. 2 h per repetition)
		for (i = 0; i < /*24*/repetitions; i++) {
                // 4 times testMoves loop followed by 10 minutes pause (total ca. 2h)
			for (j = 0; j < 4; j++) {
                // start 120 times testMoves followed by mechstop measure (total ca. 27m30s with velocity 120)
				logfile << timestamp() << ";Test;start;120\n";
				logfile.flush();
				for (k = 0; k < 120; k++) {
					if (!testMoves()) {
						i = j = k = 120;
						std::cout << "Exception or user abort.\nContinuing with mech stop measure.\n";
						continue;
					} else {
						testtotal++;
					}
				}
				if (i == 120) {
					logfile << timestamp() << ";Test;stopped\n";
				} else {
					logfile << timestamp() << ";Test;done;120\n";
				}
				logfile.flush();
				if (measuremechstops(encoders)) {
					logfile << timestamp() << ";MC";
					for (l = 0; l < numberOfMotors; l++) {
						logfile << ";" << encoders[l];
					}
					logfile << "\n";
					logfile.flush();
				} else {
					i = j = k = 120;
					std::cout << "Exception.\nContinuing with stage 4.\n";
					continue;
				}
                // end 120 times test 1 followed by mechstop measure
			}
			if (i < 24) {
				logfile << timestamp() << ";CoolDown;10\n";
				logfile.flush();
				katana->switchRobotOff();
				sleep(600);
				katana->switchRobotOn();
			}
		}
		close_keyboard();
		std::cout << "done.\n" << std::flush;
		logfile.flush();

        // read encoders after test
		std::cout << "\nSTAGE 4\nreading encoder after burn-in-test:\n- switch "
				<< "robot off with 'o'-key\n- move robot to stop positions reached"
				<< " during calibration\n- read encoders with 'e'-key\n- move "
				<< "every axis to opposite stop position\n- read encoders with "
				<< "'e'-key\n- move robot back to home position\n- press 'f'-key "
				<< "to finish this stage and end the burn-in-test\n";
		std::vector<int> enccalibafter;
		std::vector<int> encoppositafter;
		if (!readencoders(enccalibafter, encoppositafter)) {
			return -1;
		}
		logfile.flush();

        // comparing encoders
		std::cout << "\nSTAGE 5\ncomparing encoder values\n";
		logfile << timestamp() << ";MSdiff";
		std::cout << "calibration stop (before - after):";
        // i is declared in 'run test'
		for (i = 0; i < numberOfMotors; i++) {
			logfile << ";" << enccalibbefore.at(i)-enccalibafter.at(i);
			std::cout << " " << enccalibbefore.at(i)-enccalibafter.at(i);
		}
		logfile << "\n";
		logfile << timestamp() << ";MSdiff";
		std::cout << "\nopposit stop (before - after):";
		for (i = 0; i < numberOfMotors; i++) {
			logfile << ";" << encoppositbefore.at(i)-encoppositafter.at(i);
			std::cout << " " << encoppositbefore.at(i)-encoppositafter.at(i);
		}
		logfile << "\n";
		std::cout << "\n";
		logfile.flush();

        // log stats
		logfile << timestamp() << ";End;" << timestamp() << "\n";
		struct timeval endtime;
		gettimeofday(&endtime, 0);
		int sec = endtime.tv_sec - starttime.tv_sec;
		int hour = sec / 3600;
		sec -= hour * 3600;
		int min = sec / 60;
		sec -= min * 60;
		logfile << timestamp() << ";TotalTime;" << hour << ";h;" << min << ";m;" << sec << ";s\n";
		logfile << timestamp() << ";Test;iterations;" << testtotal << "\n";
		logfile << timestamp() << ";Test2;iterations;" << test2total << "\n";
		logfile.flush();

        // close logfile
		logfile.close();
		std::cout << "\nburn-in-test finished.\n";
	} catch (Exception &e) {
		std::cout << "\nERROR: " << e.message() << std::endl;
	}

	return 0;
}
