#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

class DirectiveStack;
class DirectiveTriviaSyntax;
class ExpressionSyntax;
class SyntaxNode;
class SyntaxToken;

class POLYGLOT_API DelphiDirectiveParser final : public DirectiveParser
{
public:
    explicit DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                   const DirectiveStack& context) noexcept;

    SyntaxNode* parseDirective(bool isActive,
                               bool endIsActive,
                               bool isFirstAfterTokenInFile,
                               bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
    DirectiveTriviaSyntax* parseIfDirective(SyntaxToken* openBraceDollarToken,
                                            SyntaxToken* keyword,
                                            bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfDefDirective(SyntaxToken* openBraceDollarToken,
                                               SyntaxToken* keyword,
                                               bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfNDefDirective(SyntaxToken* openBraceDollarToken,
                                                SyntaxToken* keyword,
                                                bool isActive) noexcept;

    DirectiveTriviaSyntax* parseIfEndDirective(SyntaxToken* openBraceDollarToken,
                                               SyntaxToken* keyword,
                                               bool isActive,
                                               bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseElseDirective(SyntaxToken* openBraceDollarToken,
                                              SyntaxToken* keyword,
                                              bool isActive,
                                              bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseElseIfDirective(SyntaxToken* openBraceDollarToken,
                                                SyntaxToken* keyword,
                                                bool isActive,
                                                bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseEndIfDirective(SyntaxToken* openBraceDollarToken,
                                               SyntaxToken* keyword,
                                               bool isActive,
                                               bool endIsActive) noexcept;

    DirectiveTriviaSyntax* parseDefineOrUndefDirective(SyntaxToken* openBraceDollarToken,
                                                       SyntaxToken* keyword,
                                                       bool isActive,
                                                       bool isFollowingToken) noexcept;

    DirectiveTriviaSyntax* parseRegionDirective(SyntaxToken* openBraceDollarToken,
                                                SyntaxToken* keyword,
                                                bool isActive) noexcept;

    DirectiveTriviaSyntax* parseEndRegionDirective(SyntaxToken* openBraceDollarToken,
                                                   SyntaxToken* keyword,
                                                   bool isActive) noexcept;

    SyntaxToken* parseEndOfDirective() noexcept;
    ExpressionSyntax* parseExpression() noexcept;
    ExpressionSyntax* parseLogicalOr() noexcept;
    ExpressionSyntax* parseLogicalAnd() noexcept;
    ExpressionSyntax* parseEquality() noexcept;
    ExpressionSyntax* parseLogicalNot() noexcept;
    ExpressionSyntax* parsePrimary() noexcept;
    bool evaluateBool(ExpressionSyntax* expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
