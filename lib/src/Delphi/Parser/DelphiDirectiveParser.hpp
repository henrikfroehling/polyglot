#ifndef POLYGLOT_DELPHI_PARSER_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_DELPHI_PARSER_DELPHIDIRECTIVEPARSER_H

#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/DirectiveParser.hpp"
#include "Core/Parser/Lexer.hpp"

namespace polyglot::Core::Parser
{

class DirectiveStack;

} // end namespace polyglot::Core::Parser

namespace polyglot::Core::Syntax
{

class DirectiveTriviaSyntax;
class ISyntaxToken;
class ISyntaxTrivia;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax;

} // end namespace polyglot::Delphi::Syntax

namespace polyglot::Delphi::Parser
{

class DelphiDirectiveParser final : public Core::Parser::DirectiveParser
{
public:
    explicit DelphiDirectiveParser(SharedPtr<Core::Parser::Lexer> lexer,
                                   const Core::Parser::DirectiveStack& context) noexcept;

    Core::Syntax::ISyntaxTrivia* parseDirective(bool isActive,
                                                bool endIsActive,
                                                bool isFirstAfterTokenInFile,
                                                bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
    Core::Syntax::DirectiveTriviaSyntax* parseIfDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                          Core::Syntax::ISyntaxToken* keyword,
                                                          bool isActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseIfDefDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                             Core::Syntax::ISyntaxToken* keyword,
                                                             bool isActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseIfNDefDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                              Core::Syntax::ISyntaxToken* keyword,
                                                              bool isActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseIfEndDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                             Core::Syntax::ISyntaxToken* keyword,
                                                             bool isActive,
                                                             bool endIsActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseElseDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                            Core::Syntax::ISyntaxToken* keyword,
                                                            bool isActive,
                                                            bool endIsActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseElseIfDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                              Core::Syntax::ISyntaxToken* keyword,
                                                              bool isActive,
                                                              bool endIsActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseEndIfDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                             Core::Syntax::ISyntaxToken* keyword,
                                                             bool isActive,
                                                             bool endIsActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseDefineOrUndefDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                                     Core::Syntax::ISyntaxToken* keyword,
                                                                     bool isActive,
                                                                     bool isFollowingToken) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseRegionDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                              Core::Syntax::ISyntaxToken* keyword,
                                                              bool isActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseEndRegionDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                                 Core::Syntax::ISyntaxToken* keyword,
                                                                 bool isActive) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseMessageDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                               Core::Syntax::ISyntaxToken* keyword) noexcept;

    Core::Syntax::DirectiveTriviaSyntax* parseSwitchDirective(Core::Syntax::ISyntaxToken* openBraceDollarToken,
                                                              Core::Syntax::ISyntaxToken* identifier,
                                                              Core::Syntax::ISyntaxToken* onOffToken) noexcept;

    Core::Syntax::ISyntaxToken* parseEndOfDirective() noexcept;
    Syntax::DelphiExpressionSyntax* parseExpression() noexcept;
    Syntax::DelphiExpressionSyntax* parseLogicalOr() noexcept;
    Syntax::DelphiExpressionSyntax* parseLogicalAnd() noexcept;
    Syntax::DelphiExpressionSyntax* parseEquality() noexcept;
    Syntax::DelphiExpressionSyntax* parseLogicalNot() noexcept;
    Syntax::DelphiExpressionSyntax* parsePrimary() noexcept;
    Syntax::DelphiExpressionSyntax* parseCallExpression(Core::Syntax::ISyntaxToken* identifier) noexcept;
    bool evaluateBool(Syntax::DelphiExpressionSyntax* expression) const noexcept;
    bool isDefined(pg_string_view id) const noexcept;

private:
    Core::Syntax::SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHIDIRECTIVEPARSER_H
