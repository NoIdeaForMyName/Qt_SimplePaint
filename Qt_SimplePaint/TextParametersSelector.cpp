#include "TextParametersSelector.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

QString TextParametersSelector::text = "";
int TextParametersSelector::fontSize = 10;
QString TextParametersSelector::font = fontList[0];

TextParametersSelector::TextParametersSelector(QWidget* parent)
	: QDialog(parent)
	, dataStored(false)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &TextParametersSelector::storeAllDataAndClose);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &TextParametersSelector::close);

	ui.FontInput->addItems(fontList);

	ui.TextInput->setText(text);
	ui.SizeInput->setValue(fontSize);
	ui.FontInput->setCurrentText(font);
}

TextParametersSelector::~TextParametersSelector()
{
}

bool TextParametersSelector::isDataStored()
{
	return dataStored;
}

QString& TextParametersSelector::getText()
{
	return text;
}

int TextParametersSelector::getFontSize()
{
	return fontSize;
}

QString& TextParametersSelector::getFont()
{
	return font;
}

void TextParametersSelector::storeAllDataAndClose()
{
	text = ui.TextInput->text();
	fontSize = ui.SizeInput->value();
	font = ui.FontInput->currentText();
	if (!text.isEmpty())
		dataStored = true;

	close();
}
