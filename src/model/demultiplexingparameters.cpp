#include "demultiplexingparameters.h"

#include <algorithm>

namespace
{
    bool checkPathRequired(const QString& value, const QString& label, QString* errorMessage)
    {
        if (value.trimmed().isEmpty())
        {
            if (errorMessage != nullptr)
            {
                *errorMessage = QStringLiteral("Missing %1").arg(label);
            }
            return false;
        }
        return true;
    }
}

bool DemultiplexingParameters::SequenceElement::isValid(QString* errorMessage) const
{
    switch (type)
    {
    case SequenceElementType::Constant:
    case SequenceElementType::Variable:
    case SequenceElementType::Rna:
        if (patternSource.trimmed().isEmpty())
        {
            if (errorMessage != nullptr)
            {
                *errorMessage = QStringLiteral("Sequence element \"%1\" is missing a pattern.")
                                    .arg(label.isEmpty() ? QStringLiteral("unnamed") : label);
            }
            return false;
        }
        return true;
    case SequenceElementType::Umi:
        if (umiLength <= 0)
        {
            if (errorMessage != nullptr)
            {
                *errorMessage = QStringLiteral("UMI element \"%1\" must have a positive length.")
                                    .arg(label.isEmpty() ? QStringLiteral("unnamed") : label);
            }
            return false;
        }
        return true;
    }

    if (errorMessage != nullptr)
    {
        *errorMessage = QStringLiteral("Unknown sequence element type.");
    }
    return false;
}

void DemultiplexingParameters::clear()
{
    m_forwardFastq.clear();
    m_reverseFastq.clear();
    m_outputDirectory.clear();
    m_prefix.clear();
    m_barcodePatternsFile.clear();
    m_mismatchFile.clear();
    m_threads = 1;
    m_fastqReadBucketSize = -1;
    m_independentReverseMapping = false;
    m_writeStats = false;
    m_writeFailedLines = false;
    m_writeFilesOnTheFly = false;
    m_hamming = false;
    m_sequenceElements.clear();
}

void DemultiplexingParameters::setForwardFastq(const QString& path)
{
    m_forwardFastq = path;
}

const QString& DemultiplexingParameters::forwardFastq() const
{
    return m_forwardFastq;
}

void DemultiplexingParameters::setReverseFastq(const QString& path)
{
    m_reverseFastq = path;
}

const QString& DemultiplexingParameters::reverseFastq() const
{
    return m_reverseFastq;
}

void DemultiplexingParameters::setOutputDirectory(const QString& path)
{
    m_outputDirectory = path;
}

const QString& DemultiplexingParameters::outputDirectory() const
{
    return m_outputDirectory;
}

void DemultiplexingParameters::setPrefix(const QString& value)
{
    m_prefix = value;
}

const QString& DemultiplexingParameters::prefix() const
{
    return m_prefix;
}

void DemultiplexingParameters::setThreads(int threads)
{
    m_threads = std::max(1, threads);
}

int DemultiplexingParameters::threads() const
{
    return m_threads;
}

void DemultiplexingParameters::setFastqReadBucketSize(long long bucketSize)
{
    m_fastqReadBucketSize = bucketSize;
}

long long DemultiplexingParameters::fastqReadBucketSize() const
{
    return m_fastqReadBucketSize;
}

void DemultiplexingParameters::setIndependentReverseMapping(bool enabled)
{
    m_independentReverseMapping = enabled;
}

bool DemultiplexingParameters::independentReverseMapping() const
{
    return m_independentReverseMapping;
}

void DemultiplexingParameters::setWriteStats(bool enabled)
{
    m_writeStats = enabled;
}

bool DemultiplexingParameters::writeStats() const
{
    return m_writeStats;
}

void DemultiplexingParameters::setWriteFailedLines(bool enabled)
{
    m_writeFailedLines = enabled;
}

bool DemultiplexingParameters::writeFailedLines() const
{
    return m_writeFailedLines;
}

void DemultiplexingParameters::setWriteFilesOnTheFly(bool enabled)
{
    m_writeFilesOnTheFly = enabled;
}

bool DemultiplexingParameters::writeFilesOnTheFly() const
{
    return m_writeFilesOnTheFly;
}

void DemultiplexingParameters::setHamming(bool enabled)
{
    m_hamming = enabled;
}

bool DemultiplexingParameters::hamming() const
{
    return m_hamming;
}

void DemultiplexingParameters::setBarcodePatternsFile(const QString& path)
{
    m_barcodePatternsFile = path;
}

const QString& DemultiplexingParameters::barcodePatternsFile() const
{
    return m_barcodePatternsFile;
}

void DemultiplexingParameters::setMismatchFile(const QString& path)
{
    m_mismatchFile = path;
}

const QString& DemultiplexingParameters::mismatchFile() const
{
    return m_mismatchFile;
}

void DemultiplexingParameters::addSequenceElement(const SequenceElement& element)
{
    m_sequenceElements.push_back(element);
}

void DemultiplexingParameters::setSequenceElements(const std::vector<SequenceElement>& elements)
{
    m_sequenceElements = elements;
}

const std::vector<DemultiplexingParameters::SequenceElement>& DemultiplexingParameters::sequenceElements() const
{
    return m_sequenceElements;
}

bool DemultiplexingParameters::isPairedEnd() const
{
    return !m_reverseFastq.trimmed().isEmpty();
}

bool DemultiplexingParameters::hasSequencePattern() const
{
    return !m_sequenceElements.empty();
}

bool DemultiplexingParameters::isValid(QString* errorMessage) const
{
    if (!checkPathRequired(m_forwardFastq, QStringLiteral("forward fastq path (-i)"), errorMessage))
    {
        return false;
    }

    if (!checkPathRequired(m_outputDirectory, QStringLiteral("output directory (-o)"), errorMessage))
    {
        return false;
    }

    if (!checkPathRequired(m_barcodePatternsFile, QStringLiteral("barcode patterns file (-p)"), errorMessage))
    {
        return false;
    }

    if (!checkPathRequired(m_mismatchFile, QStringLiteral("mismatch file (-m)"), errorMessage))
    {
        return false;
    }

    if (m_sequenceElements.empty())
    {
        if (errorMessage != nullptr)
        {
            *errorMessage = QStringLiteral("At least one sequence block must be added.");
        }
        return false;
    }

    for (const SequenceElement& element : m_sequenceElements)
    {
        if (!element.isValid(errorMessage))
        {
            return false;
        }
    }

    return true;
}

