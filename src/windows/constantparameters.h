#ifndef CONSTANTPARAMETERS_H
#define CONSTANTPARAMETERS_H

#include <QMainWindow>
#include "parameterbaseclass.h"

namespace Ui {
class constantparameters;
}

class constantparameters : public parameterBaseClass
{
    Q_OBJECT

public:
    explicit constantparameters(QWidget *parent = nullptr);
    ~constantparameters();

    QString get_pattern_file() override;

private:
    Ui::constantparameters *ui;
};

#endif // CONSTANTPARAMETERS_H
