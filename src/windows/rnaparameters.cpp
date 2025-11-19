#include "rnaparameters.h"
#include "ui_rnaparameters.h"

rnaparameters::rnaparameters(QWidget *parent) :
    parameterBaseClass(parent),
    ui(new Ui::rnaparameters)
{
    ui->setupUi(this);
}

rnaparameters::~rnaparameters()
{
    delete ui;
}

QString rnaparameters::get_pattern_file()
{
    return("NO FILE");
}
