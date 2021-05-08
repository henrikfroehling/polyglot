#ifndef POLYGLOT_DELPHI_PARSER_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_DELPHI_PARSER_DELPHIDIRECTIVEPARSER_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/DirectiveParser.hpp"
#include "Core/Parser/Lexer.hpp"

namespace polyglot::Delphi::Parser
{

class DirectiveStack;
class DirectiveTriviaSyntax;
class ExpressionSyntax;
class ISyntaxToken;
class ISyntaxTrivia;

class DelphiDirectiveParser final : public DirectiveParser
{
public:
    explicit DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                   const DirectiveStack& context) noexcept;

    ISyntaxTrivia* parseDirective(bool isActive,
                                  bool endIsActive,
                                  bool isFirstAfterTokenInFile,
                                  bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
    DirectiveTriviaSyntax* parseIfDirective(ISyntaxToken* openBraceDollarToken,
                                            ISyntaxToken* keyword,
                                            bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfDefDirective(ISyntaxToken* openBraceDollarToken,
                                               ISyntaxToken* keyword,
                                               bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfNDefDirective(ISyntaxToken* openBraceDollarToken,
                                                ISyntaxToken* keyword,
                                                bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfEndDirective(ISyntaxToken* openBraceDollarToken,
                                               ISyntaxToken* keyword,
                                               bool isActive,
                                               bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseElseDirective(ISyntaxToken* openBraceDollarToken,
                                              ISyntaxToken* keyword,
                                              bool isActive,
                                              bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseElseIfDirective(ISyntaxToken* openBraceDollarToken,
                                                ISyntaxToken* keyword,
                                                bool isActive,
                                                bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseEndIfDirective(ISyntaxToken* openBraceDollarToken,
                                               ISyntaxToken* keyword,
                                               bool isActive,
                                               bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseDefineOrUndefDirective(ISyntaxToken* openBraceDollarToken,
                                                       ISyntaxToken* keyword,
                                                       bool isActive,
                                                       bool isFollowingToken) noexcept;

    DirectiveTriviaSyntax* parseRegionDirective(ISyntaxToken* openBraceDollarToken,
                                                ISyntaxToken* keyword,
                                                bool isActive) noexcept;

    DirectiveTriviaSyntax* parseEndRegionDirective(ISyntaxToken* openBraceDollarToken,
                                                   ISyntaxToken* keyword,
                                                   bool isActive) noexcept;

    DirectiveTriviaSyntax* parseMessageDirective(ISyntaxToken* openBraceDollarToken,
                                                 ISyntaxToken* keyword) noexcept;

    DirectiveTriviaSyntax* parseSwitchDirective(ISyntaxToken* openBraceDollarToken,
                                                ISyntaxToken* identifier,
                                                ISyntaxToken* onOffToken) noexcept;

    ISyntaxToken* parseEndOfDirective() noexcept;
    ExpressionSyntax* parseExpression() noexcept;
    ExpressionSyntax* parseLogicalOr() noexcept;
    ExpressionSyntax* parseLogicalAnd() noexcept;
    ExpressionSyntax* parseEquality() noexcept;
    ExpressionSyntax* parseLogicalNot() noexcept;
    ExpressionSyntax* parsePrimary() noexcept;
    ExpressionSyntax* parseCallExpression(ISyntaxToken* identifier) noexcept;
    bool evaluateBool(ExpressionSyntax* expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;

private:
    SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHIDIRECTIVEPARSER_H
