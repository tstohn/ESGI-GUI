#ifndef DEMULTIPLEXINGHANDLER_H
#define DEMULTIPLEXINGHANDLER_H

#include "tools/SCDemultiplexingPipeline/src/tools/Demultiplexing/DemultiplexedLinesWriter.hpp"
#include "windows/mainwindow.h"
#include <QProgressBar>

class DemultiplexingHandler
{
public:
    DemultiplexingHandler(std::vector<parameterBaseClass*> info, QProgressBar* progressBar,
                          const DemultiplexingInput* input);

    void runDemultiplexing();
};

#endif // DEMULTIPLEXINGHANDLER_H
