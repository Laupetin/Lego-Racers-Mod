#include "SrfTextWriter.h"

namespace srf
{
    class SrfTextWriterImpl final : public ISrfEmitter
    {
    public:
        explicit SrfTextWriterImpl(std::ostream& stream)
            : m_stream(stream)
        {
        }

        void StartStrings() override
        {
        }

        void EndStrings() override
        {
        }

        void EmitString(const std::string str) override
        {
            for (const auto& c : str)
            {
                switch (c)
                {
                case '\r':
                    m_stream << "\\r";
                    break;
                case '\n':
                    m_stream << "\\n";
                    break;
                case '\\':
                    m_stream << "\\\\";
                    break;
                default:
                    m_stream << c;
                    break;
                }
            }

            m_stream << "\n";
        }

    private:
        std::ostream& m_stream;
    };
}

using namespace srf;

std::unique_ptr<ISrfEmitter> SrfTextWriter::Create(std::ostream& out)
{
    return std::make_unique<SrfTextWriterImpl>(out);
}
