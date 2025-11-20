#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/view/startwindow.h"
#include "src/controller/demultiplexingHandler.h"

#include <QGraphicsBlurEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");

    double scale = 0; //scaling factor for all images pixmap / ui-label width

    //set style elements
    //scale = ui->TopBar->width() / (double)seqBlock.width();
    //label->setFixedSize(seqBlock.width()*scale, seqBlock.height()*scale);
    //ui->TopBar->setPixmap(QPixmap(":media/TopBar.png").scaled(ui->TopBar->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //ui->TopBar->setParent(ui->centralwidget);
    //ui->TopBar->setScaledContents(true);

    //constant barcode
    QPixmap pixmapTopBar(":media/TopBar.png");
    scale = pixmapTopBar.width() / ui->TopBar->width();
    ui->TopBar->setFixedSize(pixmapTopBar.width()/scale, pixmapTopBar.height()/scale);
    ui->TopBar->setPixmap(pixmapTopBar);
    ui->TopBar->setParent(ui->centralwidget);
    ui->TopBar->setScaledContents(true);

    QPixmap pixmapLowBar(":media/LowBar.png");
    scale = pixmapLowBar.width() / ui->LowBar->width();
    ui->LowBar->setFixedSize(pixmapLowBar.width()/scale, pixmapLowBar.height()/scale);
    ui->LowBar->setPixmap(pixmapLowBar);
    ui->LowBar->setParent(ui->centralwidget);
    ui->LowBar->setScaledContents(true);

    //Load all PNGs for seauence blocks
    //constant barcode
    QPixmap originalPixmapConst(":media/ConstantSeqBlock.png");
    scale = originalPixmapConst.width() / ui->ConstantBlock->width();
    ui->ConstantBlock->setFixedSize(originalPixmapConst.width()/scale, originalPixmapConst.height()/scale);
    ui->ConstantBlock->setPixmap(originalPixmapConst);
    ui->ConstantBlock->setParent(ui->centralwidget);
    ui->ConstantBlock->set_type("constant");
    //variable barcode
    QPixmap originalPixmapVar(":media/VariableSeqBlock.png");
    scale = originalPixmapVar.width() / ui->VariableBlock->width();
    ui->VariableBlock->setFixedSize(originalPixmapVar.width()/scale, originalPixmapVar.height()/scale);
    ui->VariableBlock->setPixmap(originalPixmapVar);
    ui->VariableBlock->setParent(ui->centralwidget);
    ui->VariableBlock->set_type("variable");
    //UMI barcode
    QPixmap originalPixmapUMI(":media/UMISeqBlock.png");
    scale = originalPixmapUMI.width() / (double)ui->UMIBlock->width();
    //QPixmap scaledPixmap = originalPixmapUMI.scaled(originalPixmapUMI.width()/scale, originalPixmapUMI.height()/scale);
    ui->UMIBlock->setFixedSize(originalPixmapUMI.width()/scale, originalPixmapUMI.height()/scale);
    ui->UMIBlock->setPixmap(originalPixmapUMI);
    ui->UMIBlock->setParent(ui->centralwidget);
    ui->UMIBlock->set_type("umi");
    //scRNAseq barcode
    QPixmap originalPixmapRNA(":media/RNASeqBlock.png");
    scale = originalPixmapRNA.width() / ui->RNABlock->width();
    ui->RNABlock->setFixedSize(originalPixmapRNA.width()/scale, originalPixmapRNA.height()/scale);
    //scaledPixmap = originalPixmapRNA.scaled(originalPixmapRNA.width()/scale, originalPixmapRNA.height()/scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->RNABlock->setPixmap(originalPixmapRNA);
    ui->RNABlock->setParent(ui->centralwidget);
    ui->RNABlock->set_type("rna");

    //set progress bar to minimum
    ui->progressBar->reset();
    ui->progressBar->setVisible(false);
    ui->StatusLabel->setVisible(false);

    //disable the run button until testRun was made
    ui->RunButton->setDisabled(true);
    ui->StopButton->hide();

    //create the main scene of aligned barcodes
    scene = new QGraphicsScene();
    form = new QGraphicsWidget;
    scene->addItem(form);
    layout = new QGraphicsGridLayout(form);

    ui->ReadSequenceGraphicsView->setScene(scene);

    connect(ui->ReadSequenceGraphicsView, SIGNAL(itemdrop(SeqBlockInformation)), this, SLOT(seqBlock_enters_ReadSeqView(SeqBlockInformation)) );
    connect(ui->ClearButton, &QPushButton::clicked, this, &MainWindow::clear_selection);

}

void MainWindow::clear_demultiplexing_information()
{
    seqBlockProxyList.clear();
    seqBlockInformationList.clear();
    seqBlockImages.clear();
    seqBlockFilters.clear();

    ui->progressBar->setVisible(false);
    ui->StatusLabel->setVisible(false);
    ui->RunButton->setDisabled(true);
}

void MainWindow::clear_selection()
{
    //clear the scene
    delete form;
    scene->clear();

    //create new empty linear layout
    form = new QGraphicsWidget;
    scene->addItem(form);

    layout = new QGraphicsGridLayout(form);

    //set new scene
    ui->ReadSequenceGraphicsView->setScene(scene);
    ui->ReadSequenceGraphicsView->show();

    clear_demultiplexing_information();
}

void MainWindow::seqBlock_enters_ReadSeqView(SeqBlockInformation seqBlockInfo)
{
    QPixmap seqBlock = seqBlockInfo.barcodeImage;

    //point to baseclass: assign this to pointers of specific classes
    parameterBaseClass* parameterUi;

    //create barcode specific parameterBaseClass derived instances
    if(seqBlockInfo.barcodeType == "variable")
    {
        parameterUi = new variableParameters();
    }
    else if(seqBlockInfo.barcodeType == "umi")
    {
        parameterUi = new umiParameters();
    }
    else if(seqBlockInfo.barcodeType == "constant")
    {
        parameterUi = new constantparameters();
    }
    else if(seqBlockInfo.barcodeType == "rna")
    {
        parameterUi = new rnaparameters();
    }
    else
    {
        std::cerr << "Wrong class for barcode parameter information class!\n";
        exit(EXIT_FAILURE);
    }

    //add the table of sequence parameters for demultiplexing
    parameterUi->setFixedSize(parameterUi->width(), parameterUi->height());

    //prohibit two finger movements: for parameter-window & Barcode-labels
    NoTwoFingerGestureFilter *gestureFilter = new NoTwoFingerGestureFilter;

    //create QLabels (to keep good quality for the png files)
    QLabel *label = new QLabel();
    double scale = parameterUi->width() / (double)seqBlock.width();
    label->setFixedSize(seqBlock.width()*scale, seqBlock.height()*scale);
    label->setPixmap(seqBlock);
    label->setScaledContents(true);
    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget;
    proxyWidget->setWidget(label);
    proxyWidget->setMinimumSize(label->size());
    proxyWidget->setMaximumSize(label->size());
    proxyWidget->installEventFilter(gestureFilter);
    layout->addItem(proxyWidget, 0, numberSeqBlocks, 1, 1);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->installEventFilter(gestureFilter);
    proxy->setWidget(parameterUi);
    layout->addItem(proxy, 1, numberSeqBlocks,1,1);  // Add the widget to the first row and column

    //increase seqBlock count
    numberSeqBlocks++;
    //keeping track of all the sequence Elements that we create on heap
    seqBlockProxyList.push_back(proxy);
    seqBlockInformationList.push_back(parameterUi); //list of windows that kepe all the sequencing information
    seqBlockImages.push_back(proxyWidget);
    seqBlockFilters.push_back(gestureFilter);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete form;
    delete layout;

    clear_demultiplexing_information();
}

void MainWindow::on_HomeButton_clicked()
{
    StartWindow* startWindow = new StartWindow();
    startWindow->show();
    this->close();

    clear_demultiplexing_information();
}

DemultiplexingController::MainViewState MainWindow::collectMainViewState() const
{
    DemultiplexingController::MainViewState state;
    state.forwardFastq = ui->fwFastq->text().trimmed();
    state.reverseFastq = ui->rvFastq->text().trimmed();
    state.outputDirectory = ui->lineEdit_5->text().trimmed();
    state.threadsInput = ui->lineEdit_2->text().trimmed();
    return state;
}

bool MainWindow::check_sequence_validity()
{
    if(seqBlockInformationList.size() == 0)
    {
        startError.showMessage("Empty sequence pattern!\nPlease provide a pattern to run demultiplexing.");

        return(false);
    }

    return(true);
}

void MainWindow::on_TestButton_clicked()
{
   if(!check_sequence_validity())
   {
       return;
   }

   const auto viewState = collectMainViewState();
   QString syncError;
   if (!demultiplexingController.updateParameters(viewState, seqBlockInformationList, &syncError))
   {
       startError.showMessage(syncError);
       return;
   }
   //after update parameters call the demultiplex run function and display results
   //therefore merge the two currently existing controllers

   ui->RunButton->setEnabled(true);

}

void MainWindow::on_RunButton_clicked()
{
   if(!check_sequence_validity())
   {
       return;
   }
   ui->RunButton->hide();
   ui->StopButton->show();
   //disable all buttons: we r running an analysis and only the stop button should be activated
   QList<QPushButton *> buttonsList = this->findChildren<QPushButton *>();
   for (int i = 0; i < buttonsList.count(); i++)
   {
       if(buttonsList.at(i)->objectName() != "StopButton")
       {
           buttonsList.at(i)->setDisabled(true);
       }
   }

   ui->progressBar->setVisible(true);
   ui->StatusLabel->setVisible(true);

   const auto viewState = collectMainViewState();
   QString syncError;
   if (!demultiplexingController.updateParameters(viewState, seqBlockInformationList, &syncError))
   {
       startError.showMessage(syncError);
       return;
   }

   //fetch all the information for the demultiplexing
   DemultiplexingInput input;
   input.fwFastq = ui->fwFastq->text().toStdString();
   input.rvFastq = ui->rvFastq->text().toStdString();
   input.threads = 1;

   DemultiplexingHandler demultiplexingRun = DemultiplexingHandler(demultiplexingController.parameters(),
                                                                   ui->progressBar,
                                                                   &input);


   //QGraphicsBlurEffect* p_blur = new QGraphicsBlurEffect;
   //p_blur->setBlurRadius(10);
   //p_blur->setBlurHints(QGraphicsBlurEffect::QualityHint);
   //this->setGraphicsEffect(p_blur);
}

void MainWindow::on_StopButton_clicked()
{
    //this->setGraphicsEffect(0);

    ui->StopButton->hide();
    ui->RunButton->show();
    //enable all buttons again
    QList<QPushButton *> buttonsList = this->findChildren<QPushButton *>();
    for (int i = 0; i < buttonsList.count(); i++)
    {
        buttonsList.at(i)->setEnabled(true);
    }
}

