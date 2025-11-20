#ifndef DEMULTIPLEXINGPARAMETERS_H
#define DEMULTIPLEXINGPARAMETERS_H

#include <QString>
#include <vector>

/**
 * @brief Aggregates all user-provided inputs that are required to invoke the ESGI demultiplex tool.
 *
 * The main window assembles multiple sequence blocks (constant, variable, UMI, RNA, ...)
 * and several global parameters (fastq paths, output folder, runtime options). This model stores
 * that data in a single place so that controllers can translate it into CLI arguments or native
 * ESGI structs without querying the views again.
 */
class DemultiplexingParameters
{
public:
    enum class SequenceElementType
    {
        Constant,
        Variable,
        Umi,
        Rna
    };

    struct SequenceElement
    {
        SequenceElementType type = SequenceElementType::Constant;
        QString label;
        QString patternSource;
        int mismatches = 0;
        bool sequentialAlignment = false;
        int umiLength = 0;

        bool isValid(QString* errorMessage = nullptr) const;
    };

    void clear();

    void setForwardFastq(const QString& path);
    const QString& forwardFastq() const;

    void setReverseFastq(const QString& path);
    const QString& reverseFastq() const;

    void setOutputDirectory(const QString& path);
    const QString& outputDirectory() const;

    void setPrefix(const QString& value);
    const QString& prefix() const;

    void setThreads(int threads);
    int threads() const;

    void setFastqReadBucketSize(long long bucketSize);
    long long fastqReadBucketSize() const;

    void setIndependentReverseMapping(bool enabled);
    bool independentReverseMapping() const;

    void setWriteStats(bool enabled);
    bool writeStats() const;

    void setWriteFailedLines(bool enabled);
    bool writeFailedLines() const;

    void setWriteFilesOnTheFly(bool enabled);
    bool writeFilesOnTheFly() const;

    void setHamming(bool enabled);
    bool hamming() const;

    void setBarcodePatternsFile(const QString& path);
    const QString& barcodePatternsFile() const;

    void setMismatchFile(const QString& path);
    const QString& mismatchFile() const;

    void addSequenceElement(const SequenceElement& element);
    void setSequenceElements(const std::vector<SequenceElement>& elements);
    const std::vector<SequenceElement>& sequenceElements() const;

    bool isPairedEnd() const;
    bool hasSequencePattern() const;
    bool isValid(QString* errorMessage = nullptr) const;

private:
    QString m_forwardFastq;
    QString m_reverseFastq;
    QString m_outputDirectory;
    QString m_prefix;
    QString m_barcodePatternsFile;
    QString m_mismatchFile;

    int m_threads = 1;
    long long m_fastqReadBucketSize = -1;

    bool m_independentReverseMapping = false;
    bool m_writeStats = false;
    bool m_writeFailedLines = false;
    bool m_writeFilesOnTheFly = false;
    bool m_hamming = false;

    std::vector<SequenceElement> m_sequenceElements;
};

#endif // DEMULTIPLEXINGPARAMETERS_H

