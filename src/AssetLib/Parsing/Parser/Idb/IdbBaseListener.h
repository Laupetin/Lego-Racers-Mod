
// Generated from ..\..\..\src\AssetLib\Parsing\Parser\Idb\Idb.g4 by ANTLR 4.10.1

#pragma once

#include "IdbListener.h"
#include "antlr4-runtime.h"

namespace idb
{

    /**
     * This class provides an empty implementation of IdbListener,
     * which can be extended to create a listener which only needs to handle a subset
     * of the available methods.
     */
    class IdbBaseListener : public IdbListener
    {
    public:
        virtual void enterRoot(IdbParser::RootContext* /*ctx*/) override {}

        virtual void exitRoot(IdbParser::RootContext* /*ctx*/) override {}

        virtual void enterImages(IdbParser::ImagesContext* /*ctx*/) override {}

        virtual void exitImages(IdbParser::ImagesContext* /*ctx*/) override {}

        virtual void enterImage(IdbParser::ImageContext* /*ctx*/) override {}

        virtual void exitImage(IdbParser::ImageContext* /*ctx*/) override {}

        virtual void enterImageName(IdbParser::ImageNameContext* /*ctx*/) override {}

        virtual void exitImageName(IdbParser::ImageNameContext* /*ctx*/) override {}

        virtual void enterImageProperty(IdbParser::ImagePropertyContext* /*ctx*/) override {}

        virtual void exitImageProperty(IdbParser::ImagePropertyContext* /*ctx*/) override {}

        virtual void enterColorImageProperty(IdbParser::ColorImagePropertyContext* /*ctx*/) override {}

        virtual void exitColorImageProperty(IdbParser::ColorImagePropertyContext* /*ctx*/) override {}

        virtual void enterColorImagePropertyKeyword(IdbParser::ColorImagePropertyKeywordContext* /*ctx*/) override {}

        virtual void exitColorImagePropertyKeyword(IdbParser::ColorImagePropertyKeywordContext* /*ctx*/) override {}

        virtual void enterSingleValueKeywords(IdbParser::SingleValueKeywordsContext* /*ctx*/) override {}

        virtual void exitSingleValueKeywords(IdbParser::SingleValueKeywordsContext* /*ctx*/) override {}

        virtual void enterFloatOrIntConstant(IdbParser::FloatOrIntConstantContext* /*ctx*/) override {}

        virtual void exitFloatOrIntConstant(IdbParser::FloatOrIntConstantContext* /*ctx*/) override {}

        virtual void enterEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {}

        virtual void exitEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {}

        virtual void visitTerminal(antlr4::tree::TerminalNode* /*node*/) override {}

        virtual void visitErrorNode(antlr4::tree::ErrorNode* /*node*/) override {}
    };

} // namespace idb
