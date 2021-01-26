#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/DirectiveParser.hpp"
#include "CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

class DirectiveStack;
class DirectiveTriviaSyntax;
class ExpressionSyntax;
class LanguageSyntaxToken;
class LanguageSyntaxTrivia;

class DelphiDirectiveParser final : public DirectiveParser
{
public:
    explicit DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                   const DirectiveStack& context) noexcept;

    LanguageSyntaxTrivia* parseDirective(bool isActive,
                                         bool endIsActive,
                                         bool isFirstAfterTokenInFile,
                                         bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
    DirectiveTriviaSyntax* parseIfDirective(LanguageSyntaxToken* openBraceDollarToken,
                                            LanguageSyntaxToken* keyword,
                                            bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfDefDirective(LanguageSyntaxToken* openBraceDollarToken,
                                               LanguageSyntaxToken* keyword,
                                               bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfNDefDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                LanguageSyntaxToken* keyword,
                                                bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfEndDirective(LanguageSyntaxToken* openBraceDollarToken,
                                               LanguageSyntaxToken* keyword,
                                               bool isActive,
                                               bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseElseDirective(LanguageSyntaxToken* openBraceDollarToken,
                                              LanguageSyntaxToken* keyword,
                                              bool isActive,
                                              bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseElseIfDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                LanguageSyntaxToken* keyword,
                                                bool isActive,
                                                bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseEndIfDirective(LanguageSyntaxToken* openBraceDollarToken,
                                               LanguageSyntaxToken* keyword,
                                               bool isActive,
                                               bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseDefineOrUndefDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                       LanguageSyntaxToken* keyword,
                                                       bool isActive,
                                                       bool isFollowingToken) noexcept;

    DirectiveTriviaSyntax* parseRegionDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                LanguageSyntaxToken* keyword,
                                                bool isActive) noexcept;

    DirectiveTriviaSyntax* parseEndRegionDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                   LanguageSyntaxToken* keyword,
                                                   bool isActive) noexcept;

    DirectiveTriviaSyntax* parseMessageDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                 LanguageSyntaxToken* keyword) noexcept;

    DirectiveTriviaSyntax* parseSwitchDirective(LanguageSyntaxToken* openBraceDollarToken,
                                                LanguageSyntaxToken* identifier,
                                                LanguageSyntaxToken* onOffToken) noexcept;

    LanguageSyntaxToken* parseEndOfDirective() noexcept;
    ExpressionSyntax* parseExpression() noexcept;
    ExpressionSyntax* parseLogicalOr() noexcept;
    ExpressionSyntax* parseLogicalAnd() noexcept;
    ExpressionSyntax* parseEquality() noexcept;
    ExpressionSyntax* parseLogicalNot() noexcept;
    ExpressionSyntax* parsePrimary() noexcept;
    ExpressionSyntax* parseCallExpression(LanguageSyntaxToken* identifier) noexcept;
    bool evaluateBool(ExpressionSyntax* expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
