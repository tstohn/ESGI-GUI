#include "demultiplexingcontroller.h"

#include "../view/parameterbaseclass.h"
#include "../view/constantparameters.h"
#include "../view/variableParameters.h"
#include "../view/umiParameters.h"
#include "../view/rnaparameters.h"

#include <QLineEdit>

DemultiplexingParameters::SequenceElement DemultiplexingController::buildSequenceElement(parameterBaseClass* block) const
{
    DemultiplexingParameters::SequenceElement element;
    if (block == nullptr)
    {
        return element;
    }

    element.label = block->windowTitle();
    element.patternSource = block->get_pattern_file().trimmed();

    if (dynamic_cast<variableParameters*>(block) != nullptr)
    {
        element.type = DemultiplexingParameters::SequenceElementType::Variable;
    }
    else if (dynamic_cast<umiParameters*>(block) != nullptr)
    {
        element.type = DemultiplexingParameters::SequenceElementType::Umi;
        QLineEdit* lengthField = block->findChild<QLineEdit*>("PatternFile");
        if (lengthField != nullptr)
        {
            bool ok = false;
            const int length = lengthField->text().trimmed().toInt(&ok);
            element.umiLength = ok ? length : 0;
        }
    }
    else if (dynamic_cast<rnaparameters*>(block) != nullptr)
    {
        element.type = DemultiplexingParameters::SequenceElementType::Rna;
    }
    else
    {
        element.type = DemultiplexingParameters::SequenceElementType::Constant;
    }

    return element;
}

bool DemultiplexingController::updateParameters(const MainViewState& viewState,
                                                const std::vector<parameterBaseClass*>& sequenceBlocks,
                                                QString* errorMessage)
{
    m_parameters.clear();
    m_parameters.setForwardFastq(viewState.forwardFastq);
    m_parameters.setReverseFastq(viewState.reverseFastq);

    bool threadOk = false;
    const int requestedThreads = viewState.threadsInput.toInt(&threadOk);
    const int threads = (threadOk && requestedThreads > 0) ? requestedThreads : 1;
    m_parameters.setThreads(threads);

    m_parameters.setOutputDirectory(viewState.outputDirectory);

    std::vector<DemultiplexingParameters::SequenceElement> elements;
    elements.reserve(sequenceBlocks.size());
    for (parameterBaseClass* block : sequenceBlocks)
    {
        if (block == nullptr)
        {
            continue;
        }
        elements.push_back(buildSequenceElement(block));
    }
    m_parameters.setSequenceElements(elements);

    if (!m_parameters.hasSequencePattern())
    {
        if (errorMessage != nullptr)
        {
            *errorMessage = QStringLiteral("Empty sequence pattern! Please add at least one block.");
        }
        return false;
    }

    return true;
}

const DemultiplexingParameters& DemultiplexingController::parameters() const
{
    return m_parameters;
}

