#ifndef RNAPARAMETERS_H
#define RNAPARAMETERS_H

#include <QMainWindow>
#include "parameterbaseclass.h"

namespace Ui {
class rnaparameters;
}

class rnaparameters : public parameterBaseClass
{
    Q_OBJECT

public:
    explicit rnaparameters(QWidget *parent = nullptr);
    ~rnaparameters();

    QString get_pattern_file() override;

private:
    Ui::rnaparameters *ui;
};

#endif // RNAPARAMETERS_H
