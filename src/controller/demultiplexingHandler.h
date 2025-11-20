#ifndef DEMULTIPLEXINGHANDLER_H
#define DEMULTIPLEXINGHANDLER_H

#include "../view/mainwindow.h"
#include <QProgressBar>

// esgi related headers to run demultiplexing
#include "Barcode.hpp"
#include "Demultiplexer.hpp"

#include "../model/demultiplexingparameters.h"

class DemultiplexingHandler
{
public:
    DemultiplexingHandler(const DemultiplexingParameters& parameters, QProgressBar* progressBar,
                          const DemultiplexingInput* input);

    void runDemultiplexing();
};

#endif // DEMULTIPLEXINGHANDLER_H
