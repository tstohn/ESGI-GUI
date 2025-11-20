#include "umiParameters.h"
#include "ui_umiParameters.h"

umiParameters::umiParameters(QWidget *parent) :
    parameterBaseClass(parent),
    ui(new Ui::umiParameters)
{
    ui->setupUi(this);
}

umiParameters::~umiParameters()
{
    delete ui;
}

QString umiParameters::get_pattern_file()
{
    return(ui->PatternFile->text());
}

