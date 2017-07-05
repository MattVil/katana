/* * * * * * * *
 * GUI for the BurnInTest
 * for Neuronics internal use only
 * Author: Stefan Mueller <stefan.mueller@neuronics.ch>
 * (c) Neuronics AG   2007
 */

#ifndef BURNINTESTWINDOW_H
#define BURNINTESTWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QFileDialog>
#include <QComboBox>

class BurnInTestWindow : public QMainWindow {
	Q_OBJECT

public:
	BurnInTestWindow();

private:
	QWidget* createStartWidget();
	QWidget* createEncoderWidget();
	QWidget* createRunningWidget();

private slots:
	void browse();
	void start();
	void exit();

private:
	QLineEdit* configEdit;
	QWidget* centralWidget;
};

#endif
