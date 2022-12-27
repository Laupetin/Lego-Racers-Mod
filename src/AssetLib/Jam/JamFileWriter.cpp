#include "JamFileWriter.h"

using namespace jam;

class JamFileWriterImpl final : public IJamFileWriter
{
public:
    explicit JamFileWriterImpl(std::ostream& stream)
        : m_stream(stream)
    {
    }

    void PrepareDirectoryTree(DirectoryTree& tree) override
    {
        // TODO
    }

    void WriteDataForFile(const jam_id_t& file, std::istream& stream) override
    {
        // TODO
    }

    void WriteMetaData() override
    {
        // TODO
    }

private:
    std::ostream& m_stream;
};

std::unique_ptr<IJamFileWriter> IJamFileWriter::Create(std::ostream& stream)
{
    return std::make_unique<JamFileWriterImpl>(stream);
}
