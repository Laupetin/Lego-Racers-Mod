#include "GdbTextReader.h"

#include <iostream>

#include "Gdb.h"

#pragma warning(push, 0)
#include "Parsing/Common/CommonGrammarHelper.h"
#include "Parsing/Parser/Gdb/GdbLexer.h"
#include "Parsing/Parser/Gdb/GdbParser.h"
#include "Parsing/Parser/Gdb/GdbBaseListener.h"
#pragma warning(pop)

namespace gdb
{
    class GdbCreationException final : public std::exception
    {
    public:
        explicit GdbCreationException(std::string str)
            : exception(str.c_str()),
              m_message(std::move(str))
        {
        }

    private:
        std::string m_message;
    };

    class CustomGdbListener final : public GdbBaseListener
    {
    public:
        explicit CustomGdbListener(GdbParser& parser, IGdbEmitter& emitter)
            : m_parser(parser),
              m_emitter(emitter)
        {
        }

        void enterMaterialSection(GdbParser::MaterialSectionContext* ctx) override 
        {
            m_emitter.StartMaterials();
        }

        void exitMaterialName(GdbParser::MaterialNameContext* ctx) override 
        {
            m_emitter.EmitMaterial(common_grammar::StringValue(ctx->StringLiteral()));
        }

        void exitMaterialSection(GdbParser::MaterialSectionContext* ctx) override 
        {
            m_emitter.EndMaterials();
        }

        void exitScaleSection(GdbParser::ScaleSectionContext* ctx) override 
        {
            m_emitter.EmitScale(GetFloat(ctx->floatOrIntConstant()));
        }

        void enterVertexSection(GdbParser::VertexSectionContext* ctx) override 
        {
            m_emitter.StartVertices();
        }

        void exitVertexDefPositionUv(GdbParser::VertexDefPositionUvContext* ctx) override 
        {
            const auto position = GetVertexPosition(ctx->vertexPosition());
            const auto uv = GetVertexUv(ctx->vertexUv());

            m_emitter.EmitVertex(position, uv);
        }

        void exitVertexDefPositionUvColor(GdbParser::VertexDefPositionUvColorContext* ctx) override 
        {
            const auto position = GetVertexPosition(ctx->vertexPosition());
            const auto uv = GetVertexUv(ctx->vertexUv());
            const auto color = GetVertexColor(ctx->vertexColor());

            m_emitter.EmitVertex(position, uv, color);
        }

        void exitVertexDefPositionUvNormal(GdbParser::VertexDefPositionUvNormalContext* ctx) override 
        {
            const auto position = GetVertexPosition(ctx->vertexPosition());
            const auto uv = GetVertexUv(ctx->vertexUv());
            const auto normal = GetVertexNormal(ctx->vertexNormal());

            m_emitter.EmitVertex(position, uv, normal);
        }

        void exitVertexDefPosition(GdbParser::VertexDefPositionContext* ctx) override 
        {
            const auto position = GetVertexPosition(ctx->vertexPosition());

            m_emitter.EmitVertex(position);
        }

        void exitVertexSection(GdbParser::VertexSectionContext* ctx) override 
        {
            m_emitter.EndVertices();
        }

        void enterFaceSection(GdbParser::FaceSectionContext* ctx) override 
        {
            m_emitter.StartFaces();
        }

        void exitFace(GdbParser::FaceContext* ctx) override 
        {
            const auto vertex0 = GetUnsignedInt(ctx->IntegerConstant(0));
            const auto vertex1 = GetUnsignedInt(ctx->IntegerConstant(1));
            const auto vertex2 = GetUnsignedInt(ctx->IntegerConstant(2));

            m_emitter.EmitFace(vertex0, vertex1, vertex2);
        }

        void exitFaceSection(GdbParser::FaceSectionContext* ctx) override 
        {
            m_emitter.EndFaces();
        }

        void enterMetaSection(GdbParser::MetaSectionContext* ctx) override 
        {
            m_emitter.StartMeta();
        }

        void exitKeyword31(GdbParser::Keyword31Context* ctx) override 
        {
            const auto value0 = GetInt(ctx->IntegerConstant(0));
            const auto value1 = GetInt(ctx->IntegerConstant(1));
            const auto value2 = GetInt(ctx->IntegerConstant(2));

            m_emitter.EmitMetaKeyword31(value0, value1, value2);
        }

        void exitKeyword2D(GdbParser::Keyword2DContext* ctx) override 
        {
            const auto value0 = GetInt(ctx->IntegerConstant(0));
            const auto value1 = GetInt(ctx->IntegerConstant(1));

            m_emitter.EmitMetaKeyword2D(value0, value1);
        }

        void exitKeyword2F(GdbParser::Keyword2FContext* ctx) override 
        {
            const auto value0 = GetInt(ctx->IntegerConstant());

            m_emitter.EmitMetaKeyword2F(value0);
        }

        void exitKeyword30(GdbParser::Keyword30Context* ctx) override 
        {
            m_emitter.EmitMetaKeyword30();
        }

        void exitKeyword32(GdbParser::Keyword32Context* ctx) override 
        {
            const auto value0 = GetInt(ctx->IntegerConstant());

            m_emitter.EmitMetaKeyword32(value0);
        }

        void exitKeyword27(GdbParser::Keyword27Context* ctx) override 
        {
            const auto value0 = GetInt(ctx->IntegerConstant());

            m_emitter.EmitMetaKeyword27(value0);
        }

        void exitMetaSection(GdbParser::MetaSectionContext* ctx) override 
        {
            m_emitter.EndMeta();
        }

    private:
        Vec3 GetVertexPosition(GdbParser::VertexPositionContext* ctx) const
        {
            Vec3 value;
            value.x = GetFloat(ctx->floatOrIntConstant(0));
            value.y = GetFloat(ctx->floatOrIntConstant(1));
            value.z = GetFloat(ctx->floatOrIntConstant(2));

            return value;
        }

        Vec2 GetVertexUv(GdbParser::VertexUvContext* ctx) const
        {
            Vec2 value;
            value.x = GetFloat(ctx->floatOrIntConstant(0));
            value.y = GetFloat(ctx->floatOrIntConstant(1));

            return value;
        }

        Color4 GetVertexColor(GdbParser::VertexColorContext* ctx) const
        {
            Color4 value;
            value.r = GetUInt8(ctx->IntegerConstant(0));
            value.g = GetUInt8(ctx->IntegerConstant(1));
            value.b = GetUInt8(ctx->IntegerConstant(2));
            value.a = GetUInt8(ctx->IntegerConstant(3));

            return value;
        }

        Vec3 GetVertexNormal(GdbParser::VertexNormalContext* ctx) const
        {
            Vec3 value;
            value.x = GetFloat(ctx->floatOrIntConstant(0));
            value.y = GetFloat(ctx->floatOrIntConstant(1));
            value.z = GetFloat(ctx->floatOrIntConstant(2));

            return value;
        }

        uint8_t GetUInt8(antlr4::tree::TerminalNode* node) const
        {
            uint8_t value;
            if (!common_grammar::UInt8Value(node, value))
                m_parser.notifyErrorListeners(node->getSymbol(), "Invalid uint8 value", nullptr);

            return value;
        }

        int GetInt(antlr4::tree::TerminalNode* node) const
        {
            int value;
            if (!common_grammar::IntValue(node, value))
                m_parser.notifyErrorListeners(node->getSymbol(), "Invalid int value", nullptr);

            return value;
        }

        unsigned int GetUnsignedInt(antlr4::tree::TerminalNode* node) const
        {
            unsigned int value;
            if (!common_grammar::UnsignedIntValue(node, value))
                m_parser.notifyErrorListeners(node->getSymbol(), "Invalid unsigned int value", nullptr);

            return value;
        }

        float GetFloat(GdbParser::FloatOrIntConstantContext* ctx) const
        {
            float value;
            if (!common_grammar::FloatingOrIntValue(ctx, value))
                m_parser.notifyErrorListeners(ctx->getStart(), "Invalid float value", nullptr);

            return value;
        }

        GdbParser& m_parser;
        IGdbEmitter& m_emitter;
    };

    class CustomGdbErrorListener final : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override
        {
            std::ostringstream ss;
            ss << "Parsing GDB failed: L" << line << ':' << charPositionInLine << " " << msg;

            throw GdbCreationException(ss.str());
        }
    };

	class GdbTextReaderImpl
	{
	public:
		GdbTextReaderImpl(std::istream& in, IGdbEmitter& emitter)
			: m_stream(in),
			  m_emitter(emitter)
		{
		}

		void Read() const
        {
            CustomGdbErrorListener errors;
            antlr4::ANTLRInputStream inputStream(m_stream);

            GdbLexer lexer(&inputStream);
            lexer.addErrorListener(&errors);

            antlr4::CommonTokenStream tokenStream(&lexer);
            GdbParser parser(&tokenStream);
            parser.addErrorListener(&errors);

            auto* parseTree = parser.root();

            CustomGdbListener listener(parser, m_emitter);
            antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parseTree);
		}

		std::istream& m_stream;
		IGdbEmitter& m_emitter;
	};
}

using namespace gdb;

void GdbTextReader::Read(std::istream& input, IGdbEmitter& emitter)
{
    const GdbTextReaderImpl impl(input, emitter);
	impl.Read();
}