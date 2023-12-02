#include "SrfCreator.h"

#include "SrfBinaryWriter.h"
#include "SrfTextReader.h"

namespace srf
{
    bool SrfCreator::SupportFileExtension(const std::string& extension) const
    {
        return extension == ".SRF";
    }

    void SrfCreator::ProcessFile(const std::string& filePath, std::istream& input, std::ostream& output) const
    {
        std::cout << "Srf creating \"" << filePath << "\"\n";

        const auto writer = SrfBinaryWriter::Create(output);
        SrfTextReader::Read(input, *writer);
    }
} // namespace srf
