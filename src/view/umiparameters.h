#ifndef UMIPARAMETERS_H
#define UMIPARAMETERS_H

#include <QMainWindow>
#include "parameterbaseclass.h"

namespace Ui {
class umiParameters;
}

class umiParameters : public parameterBaseClass
{
    Q_OBJECT

public:
    explicit umiParameters(QWidget *parent = nullptr);
    ~umiParameters();

    QString get_pattern_file() override;

private:
    Ui::umiParameters *ui;
};

#endif // UMIPARAMETERS_H
