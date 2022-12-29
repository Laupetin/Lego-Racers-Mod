#include "SrfTextReader.h"

#include <iostream>
#include <sstream>

namespace srf
{
    class SrfCreationException final : public std::exception
    {
    public:
        explicit SrfCreationException(std::string msg)
            : m_msg(std::move(msg))
        {
        }

        [[nodiscard]] char const* what() const noexcept override
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

    class SrfTextReaderImpl
    {
    public:
        SrfTextReaderImpl(std::istream& in, ISrfEmitter& emitter)
            : m_stream(in),
              m_emitter(emitter)
        {
        }

        void Read() const
        {
            m_emitter.StartStrings();

            bool hasStringData = false;
            std::ostringstream ss;

            while (!m_stream.eof())
            {
                auto c = m_stream.get();

            handle_letter:
                switch (c)
                {
                case '\\':
                    {
                        const auto c1 = m_stream.get();
                        if (c1 != EOF)
                        {
                            if (c1 == 'r')
                                ss << "\r";
                            else if (c1 == 'n')
                                ss << "\n";
                            else
                                ss << c1;
                            hasStringData = true;
                        }
                        else
                            throw SrfCreationException("Last character of Srf cannot be \\");
                        break;
                    }

                case '\r':
                    {
                        const auto c1 = m_stream.get();
                        if (c1 == '\n')
                        {
                            if (hasStringData)
                            {
                                m_emitter.EmitString(ss.str());
                                ss.str(std::string());
                                hasStringData = false;
                            }
                        }
                        else
                        {
                            ss << static_cast<char>(c);
                            hasStringData = true;
                            c = c1;
                            goto handle_letter;
                        }
                        break;
                    }

                case '\n':
                    if (hasStringData)
                    {
                        m_emitter.EmitString(ss.str());
                        ss.str(std::string());
                        hasStringData = false;
                    }
                    break;

                case EOF:
                    break;

                default:
                    ss << static_cast<char>(c);
                    hasStringData = true;
                    break;
                }
            }

            if (hasStringData)
                m_emitter.EmitString(ss.str());

            m_emitter.EndStrings();
        }

        std::istream& m_stream;
        ISrfEmitter& m_emitter;
    };
}

using namespace srf;

void SrfTextReader::Read(std::istream& input, ISrfEmitter& emitter)
{
    const SrfTextReaderImpl impl(input, emitter);
    impl.Read();
}
