#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui { class StartWindow; }

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_DemultiplexButton_clicked();

private:
    Ui::StartWindow* ui;
    MainWindow* mw;
};
#endif // STARTWINDOW_H
