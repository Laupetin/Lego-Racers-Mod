#include "SrfDumper.h"

#include "SrfBinaryReader.h"
#include "SrfTextWriter.h"

namespace srf
{
    bool SrfDumper::SupportFileExtension(const std::string& extension) const
    {
        return extension == ".SRF";
    }

    void SrfDumper::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
    {
        std::cout << "SRF dumping \"" << filePath << "\"\n";

        const auto writer = SrfTextWriter::Create(output);
        SrfBinaryReader::Read(input, *writer);
    }
} // namespace srf
