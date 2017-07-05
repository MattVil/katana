/* * * * * * * *
 * GUI for the BurnInTest
 * for Neuronics internal use only
 * Author: Stefan Mueller <stefan.mueller@neuronics.ch>
 * (c) Neuronics AG   2007
 */

#include "BurnInTestWindow.h"

BurnInTestWindow::BurnInTestWindow() {
	// layouts
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QGridLayout* editLayout = new QGridLayout;
	QHBoxLayout* buttonLayout = new QHBoxLayout;

	mainLayout->addLayout(editLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(buttonLayout);

	// labels and text boxes
	QLabel* sn = new QLabel(tr("Katana SN:"));
	QLineEdit* snEdit = new QLineEdit;
	QLabel* ip = new QLabel(tr("IP:"));
	QLineEdit* ipEdit = new QLineEdit;
	QLabel* port = new QLabel(tr("Port:"));
	QLineEdit* portEdit = new QLineEdit;
	QLabel* hours = new QLabel(tr("Hours:"));
	QLineEdit* hoursEdit = new QLineEdit;
	QLabel* configFile = new QLabel(tr("Config File:"));
	configEdit = new QLineEdit;
	QPushButton* browse = new QPushButton("Browse...");
	connect(browse, SIGNAL(clicked()), this, SLOT(browse()));


	editLayout->addWidget(sn, 0, 0);
	editLayout->addWidget(snEdit, 0, 1);
	editLayout->addWidget(ip, 1, 0);
	editLayout->addWidget(ipEdit, 1, 1);
	editLayout->addWidget(port, 2, 0);
	editLayout->addWidget(portEdit, 2, 1);
	editLayout->addWidget(hours, 3, 0);
	editLayout->addWidget(hoursEdit, 3, 1);
	editLayout->addWidget(configFile, 4, 0);
	editLayout->addWidget(configEdit, 4, 1);
	editLayout->addWidget(browse, 4, 2);

	// buttons
	QPushButton* start = new QPushButton(tr("Start"));
	connect(start, SIGNAL(clicked()), this, SLOT(start()));
	QPushButton* exit = new QPushButton(tr("Exit"));
	connect(exit, SIGNAL(clicked()), this, SLOT(exit()));

	buttonLayout->addWidget(exit);
	buttonLayout->addStretch();
	buttonLayout->addWidget(start);

	centralWidget = new QWidget;
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	resize(480, 220);
	setWindowTitle("Neuronics AG - BurnInTest");
}

void BurnInTestWindow::browse() {
	QString directory = QFileDialog::getOpenFileName(this, tr("Find Files"), QDir::currentPath(), tr("Config files (*.cfg)"));
	if (!directory.isEmpty()) {
         configEdit->setText(directory);
	}
}

void BurnInTestWindow::start() {
	
}

void BurnInTestWindow::exit() {

}

QWidget* BurnInTestWindow::createStartWidget() {

}

QWidget* BurnInTestWindow::createEncoderWidget() {

}

QWidget* BurnInTestWindow::createRunningWidget() {

}
