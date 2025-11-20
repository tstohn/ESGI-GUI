#ifndef VARIABLEPARAMETERS_H
#define VARIABLEPARAMETERS_H

#include <QMainWindow>
#include "parameterbaseclass.h"

namespace Ui {
class variableParameters;
}

class variableParameters : public parameterBaseClass
{
    Q_OBJECT

public:
    explicit variableParameters(QWidget *parent = nullptr);
    ~variableParameters();

    QString get_pattern_file() override;

private:
    Ui::variableParameters *ui;
};

#endif // VARIABLEPARAMETERS_H
