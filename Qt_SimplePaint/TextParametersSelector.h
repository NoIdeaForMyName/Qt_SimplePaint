#pragma once
#include <QtWidgets/QDialog>
#include <qdialog.h>
#include "ui_TextParametersSelector.h"

const QStringList fontList = {
    "Arial",
    "Times New Roman",
    "Courier New",
    "Verdana",
    "Tahoma",
    "Helvetica",
    "Comic Sans MS",
    "Georgia",
    "Trebuchet MS",
    "Impact"
};

class TextParametersSelector : public QDialog
{
    Q_OBJECT

public:
    TextParametersSelector(QWidget* parent = nullptr);
    ~TextParametersSelector();

    bool isDataStored();
    static QString& getText();
    static int getFontSize();
    static QString& getFont();

private slots:
    void storeAllDataAndClose();

private:
    Ui::TextParametersSelectorClass ui;
    bool dataStored;
    static QString text;
    static int fontSize;
    static QString font;
};
