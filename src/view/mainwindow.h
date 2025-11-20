#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include "qpixmaplayoutitem.h"
#include "demultiplexingcontroller.h"
#include <iostream>
#include <QGraphicsProxyWidget>
#include <QEvent>
#include <QGestureEvent>
#include <QErrorMessage>
#include "readassemblyevents.h"
#include "variableparameters.h"
#include "umiparameters.h"
#include "constantparameters.h"
#include "rnaparameters.h"

//two finger movements inside the seqBlockParameters.ui causes crash
//therefore disable this event
class NoTwoFingerGestureFilter : public QObject {
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::GraphicsSceneWheel ) {
            return true; // Ignore the touch and gesture events
        }
        return QObject::eventFilter(obj, event);
    }
};

namespace Ui
{
    class MainWindow;
}

struct DemultiplexingInput
{
    std::string fwFastq;
    std::string rvFastq;
    int threads = 1;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        QGraphicsScene* scene;
        QGraphicsGridLayout *layout;
        QGraphicsWidget *form;
        int numberSeqBlocks = 0;
        QErrorMessage startError;

        std::vector<QGraphicsProxyWidget*> seqBlockProxyList;
        std::vector<parameterBaseClass*> seqBlockInformationList;
        std::vector<QGraphicsProxyWidget*> seqBlockImages;
        std::vector<NoTwoFingerGestureFilter*> seqBlockFilters;
        DemultiplexingController demultiplexingController;

        DemultiplexingController::MainViewState collectMainViewState() const;

    private slots:
        void seqBlock_enters_ReadSeqView(SeqBlockInformation seqBlock);
        void clear_selection();
        void on_HomeButton_clicked();
        void on_TestButton_clicked();
        void on_RunButton_clicked();
        void on_StopButton_clicked();
        void clear_demultiplexing_information();
        bool check_sequence_validity();

};

#endif // MAINWINDOW_H
