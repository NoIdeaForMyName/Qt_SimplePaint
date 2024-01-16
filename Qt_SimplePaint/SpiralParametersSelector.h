#pragma once
#include <QDialog>
#include "ui_SpiralParametersSelector.h"

const QString wrong_input_txt = "ERROR";

const int space = ' ';
const int dot = '.';
const int first_digit = '0';
const int last_digit = '9';

class SpiralParametersSelector : public QDialog
{
	Q_OBJECT

public:
	SpiralParametersSelector(QWidget* parent = nullptr);

	bool isStored();
	static double getA();
	static double getB();
	static double getStart();
	static double getEnd();

private slots:
	void storeAllData();

private:
	Ui::SpiralParametersSelectorClass ui;
	static double a, b, start, end;
	bool stored;

};
