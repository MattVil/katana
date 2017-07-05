#include "kniBase.h"
#include "KNI/kmlMotBase.h"
#include "common/Timer.h"

#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include <fstream>
#include <pthread.h>


#ifdef WIN32
#	include <conio.h>
#else //LINUX
#	include "keyboard.h"
#endif

#define LEFT false
#define RIGHT true
#define PASSMARK_BALL 110
#define PASSMARK_HAND 110

//Thread structs:
pthread_mutex_t mutex;

struct TPoint {
	double X, Y, Z;
	double phi, theta, psi;
};

struct TCurrentMot {
	int idx;
	bool running;
	bool dir;
};

struct Tpos{
	static std::vector<int> x,y,z,u,v,w,q,r;
	static const int xArr[], yArr[], zArr[], uArr[], vArr[], wArr[], qArr[], rArr[];
};
//Katana obj.
std::auto_ptr<CCdlCOM> device;
std::auto_ptr<CCplSerialCRC> protocol;
std::auto_ptr<CLMBase> katana;
//std::vector<int> Foo::vec(array, array + sizeof(array)/sizeof(*array));

//positionen, hard-coded. Use values from file instead
const int Tpos::xArr[] = {7784, -29016, -22954, 26348, 30990, 20807};//Init
const int Tpos::yArr[] = {20540, -23898, -30196, 26035, 30900, 21402};//Richtung Ecke1
const int Tpos::zArr[] = {20540, -23898, -30196, 26035, 18941, 21402};//Ecke1 unten
const int Tpos::uArr[] = {7473, -26189, -16312, 22620, 12371, 21405};//Richtung Ecke2
const int Tpos::vArr[] = {7858, -21473, -26966, 19286, 19258, 21405};//Ecke2 unten
const int Tpos::wArr[] = {-3906, -21472, -26966, 19288, 19258, 21405};//Vorne unten
const int Tpos::qArr[] = {-3906, -21472, -26966, 19288, 19258, 30993};//Vorne oben
const int Tpos::rArr[] = {15478, -12910, -14248, 14215, -4739, 29829};//
std::vector<int> Tpos::x(xArr, xArr + sizeof(xArr)/sizeof(*xArr));
std::vector<int> Tpos::y(yArr, yArr + sizeof(yArr)/sizeof(*yArr));
std::vector<int> Tpos::z(zArr, zArr + sizeof(zArr)/sizeof(*zArr));
std::vector<int> Tpos::u(uArr, uArr + sizeof(uArr)/sizeof(*uArr));
std::vector<int> Tpos::v(vArr, vArr + sizeof(vArr)/sizeof(*vArr));
std::vector<int> Tpos::w(wArr, wArr + sizeof(wArr)/sizeof(*wArr));
std::vector<int> Tpos::q(qArr, qArr + sizeof(qArr)/sizeof(*qArr));
std::vector<int> Tpos::r(rArr, rArr + sizeof(rArr)/sizeof(*rArr));
std::vector<TPoint> points(0);

void StartPointlistMovement();
void StartProgram(int index);
pthread_t tid;
void* RunProgram(void*);
pid_t threadPid;
int retVal = 0;

bool progRunning = false;
const double PI = 3.14159265358979323846;

int main(int argc, char *argv[]) {

	if (argc != 3) {
		std::cout << "--------------------------------\n";
		std::cout << "usage: positions CONFIGFILE PORT\n";
		std::cout << "--------------------------------\n";
		return 0;
	}

	int port = atoi(argv[2]);

	std::cout << "----------------------\n";
	std::cout << "POSITIONS DEMO STARTED\n";
	std::cout << "----------------------\n";

	//----------------------------------------------------------------//
	//open device: a serial port is opened in this case
	//----------------------------------------------------------------//

	try {
		TCdlCOMDesc ccd = {port, 57600, 8, 'N', 1, 300, 0};
		device.reset(new CCdlCOM(ccd));

		std::cout << "-------------------------------------------\n";
		std::cout << "success: serial port " << port << " open\n";
		std::cout << "-------------------------------------------\n";

		//--------------------------------------------------------//
		//init protocol:
		//--------------------------------------------------------//

		protocol.reset(new CCplSerialCRC());
		protocol->init(device.get());
		std::cout << "-------------------------------------------\n";
		std::cout << "success: protocol initiated\n";
		std::cout << "-------------------------------------------\n";


		//--------------------------------------------------------//
		//init robot:
		//--------------------------------------------------------//

		katana.reset(new CLMBase());
		katana->create(argv[1], protocol.get());

	} catch(Exception &e) {
		std::cout << "ERROR: " << e.message() << std::endl;
		return -1;
	}
	std::cout << "-------------------------------------------\n";
	std::cout << "success: katana initiated\n";
	std::cout << "-------------------------------------------\n";
	try{
		bool loop = true;
		std::vector<int> encoders(katana->getNumberOfMotors(), 0);
		TCurrentMot mot[6];
		for (int i = 0; i< 6; i++){
			mot[i].running = false;
			mot[i].idx = i;
			mot[i].dir = true;
			mot[i].dir = RIGHT;
		}
		katana->calibrate();
		//katana->moveRobotToEnc(Tpos::x, true);
		katana->setRobotVelocityLimit(100);
		katana->setRobotAccelerationLimit(1);
		int limit = 10;
		for(short motorNumber = 0; motorNumber < katana->getNumberOfMotors(); ++motorNumber) {
			katana->setCrashLimit(motorNumber, limit);
		}
		//katana->enableCrashLimits();
	//x,y,z,u,v,w,q,r;
		while(loop){
			try{
				//katana->moveMotorToEnc(0, 12241, true);
				katana->moveRobotToEnc(Tpos::x, true);
				katana->moveRobotToEnc(Tpos::y, true);
				//katana->moveMotorToEnc(3, 6732, true);
				katana->moveRobotToEnc(Tpos::z, true);
				//katana->moveMotorToEnc(0, 8112, true);
				//katana->setRobotVelocityLimit(180);
				katana->moveRobotToEnc(Tpos::u, true);
				//katana->moveMotorToEnc(3, 6732, true);
				katana->moveRobotToEnc(Tpos::x, true);
				katana->moveRobotToEnc(Tpos::w, true);
				//katana->setRobotVelocityLimit(180);
				katana->moveRobotToEnc(Tpos::q, true);
				//katana->setRobotVelocityLimit(180);
				//katana->moveMotorToEnc(4, 22903, true);
				//katana->moveMotorToEnc(4, -12180, true);
				//katana->moveMotorToEnc(4, -4739, true);
				katana->setRobotVelocityLimit(100);
				//katana->setRobotVelocityLimit(100);
				//katana->setRobotVelocityLimit(100);
				//katana->moveRobotToEnc(Tpos::x, true);
				
				//katana->moveMotorToEnc(0, 8112, true);
				//katana->moveRobotToEnc(Tpos::w, true);
				//katana->moveRobotToEnc(Tpos::q, true);
				//katana->setRobotVelocityLimit(180);
				//katana->moveMotorToEnc(4, 22903, true);
				//katana->moveMotorToEnc(4, -12180, true);
				//katana->moveMotorToEnc(4, -4739, true);
				//katana->setRobotVelocityLimit(100);
				//katana->setRobotVelocityLimit(100);
				
			}catch (Exception &e) {
				std::cout << "\nERROR: " << e.message() << std::endl;
			}
		}
	}catch (Exception &e) {
		std::cout << "\nERROR: " << e.message() << std::endl;
	}
	return 0;
}
