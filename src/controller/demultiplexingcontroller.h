#ifndef DEMULTIPLEXINGCONTROLLER_H
#define DEMULTIPLEXINGCONTROLLER_H

#include <QString>
#include <vector>

#include "../model/demultiplexingparameters.h"

class parameterBaseClass;
class constantparameters;
class variableParameters;
class umiParameters;
class rnaparameters;

class DemultiplexingController
{
public:
    struct MainViewState
    {
        QString forwardFastq;
        QString reverseFastq;
        QString outputDirectory;
        QString threadsInput;
    };

    bool updateParameters(const MainViewState& viewState,
                          const std::vector<parameterBaseClass*>& sequenceBlocks,
                          QString* errorMessage = nullptr);

    const DemultiplexingParameters& parameters() const;

private:
    DemultiplexingParameters m_parameters;

    DemultiplexingParameters::SequenceElement buildSequenceElement(parameterBaseClass* block) const;
};

#endif // DEMULTIPLEXINGCONTROLLER_H

