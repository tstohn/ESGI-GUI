#include "variableParameters.h"
#include "ui_variableParameters.h"

variableParameters::variableParameters(QWidget *parent) :
    parameterBaseClass(parent),
    ui(new Ui::variableParameters)
{
    ui->setupUi(this);
}

variableParameters::~variableParameters()
{
    delete ui;
}

QString variableParameters::get_pattern_file()
{
    return(ui->PatternFile->text());
}

