#ifndef PARAMETERBASECLASS_H
#define PARAMETERBASECLASS_H

#include <QMainWindow>

namespace Ui {
class parameterBaseClass;
}

class parameterBaseClass : public QMainWindow
{
    Q_OBJECT

public:
    parameterBaseClass(QWidget *parent = nullptr):QMainWindow(parent){}
    virtual QString get_pattern_file() = 0;

private:

};



#endif // PARAMETERBASECLASS_H
