#include "constantparameters.h"
#include "ui_constantparameters.h"

constantparameters::constantparameters(QWidget *parent) :
    parameterBaseClass(parent),
    ui(new Ui::constantparameters)
{
    ui->setupUi(this);
}

constantparameters::~constantparameters()
{
    delete ui;
}

QString constantparameters::get_pattern_file()
{
    return(ui->PatternFile->text());
}

