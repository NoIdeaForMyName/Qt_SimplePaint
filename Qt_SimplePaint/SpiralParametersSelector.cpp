#include "SpiralParametersSelector.h"

#include <qmessagebox.h>

double SpiralParametersSelector::a = 0.30635;
double SpiralParametersSelector::b = 1;
double SpiralParametersSelector::start = 0;
double SpiralParametersSelector::end = 6.28;

SpiralParametersSelector::SpiralParametersSelector(QWidget* parent)
	: stored(false)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &SpiralParametersSelector::storeAllData);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &SpiralParametersSelector::close);

	ui.A_edit->setText(QString::number(a));
	ui.B_edit->setText(QString::number(b));
	ui.Start_edit->setText(QString::number(start));
	ui.End_edit->setText(QString::number(end));
}

void SpiralParametersSelector::storeAllData()
{
	bool globalOk = true;
	bool* ok = new bool(true);

	a = ui.A_edit->text().toDouble(ok);
	if (!*ok)
	{
		ui.A_edit->setText(wrong_input_txt);
		globalOk = false;
	}

	b = ui.B_edit->text().toDouble(ok);
	if (!*ok)
	{
		ui.B_edit->setText(wrong_input_txt);
		globalOk = false;
	}

	start = ui.Start_edit->text().toDouble(ok);
	if (!*ok)
	{
		ui.Start_edit->setText(wrong_input_txt);
		globalOk = false;
	}

	end = ui.End_edit->text().toDouble(ok);
	if (!*ok)
	{
		ui.End_edit->setText(wrong_input_txt);
		globalOk = false;
	}

	if (globalOk)
	{
		stored = true;
		close();
	}
	else // WARNING
		QMessageBox::warning(nullptr, "Warning", wrong_input_txt);

	delete ok;
}

bool SpiralParametersSelector::isStored()
{
	return stored;
}

double SpiralParametersSelector::getA()
{
	return a;
}

double SpiralParametersSelector::getB()
{
	return b;
}

double SpiralParametersSelector::getStart()
{
	return start;
}

double SpiralParametersSelector::getEnd()
{
	return end;
}

