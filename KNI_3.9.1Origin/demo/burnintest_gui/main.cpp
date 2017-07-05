/* * * * * * * *
 * GUI for the BurnInTest
 * for Neuronics internal use only
 * Author: Stefan Mueller <stefan.mueller@neuronics.ch>
 * (c) Neuronics AG   2007
 */

#include <QApplication>
#include "BurnInTestWindow.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	BurnInTestWindow btw;
	btw.show();

	return a.exec();
}
