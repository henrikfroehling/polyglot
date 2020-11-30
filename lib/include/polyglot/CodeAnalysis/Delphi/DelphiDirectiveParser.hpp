#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxFacts.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiDirectiveParser final : public DirectiveParser
{
public:
    explicit DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                   const DirectiveStack& context,
                                   SharedPtr<SyntaxFacts> syntaxFacts) noexcept;

    SharedPtr<SyntaxNode> parseDirective(bool isActive,
                                         bool endIsActive,
                                         bool isFirstAfterTokenInFile,
                                         bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
    SharedPtr<DirectiveTriviaSyntax> parseIfDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                      SharedPtr<SyntaxToken> keyword,
                                                      bool isActive) noexcept;

    SharedPtr<DirectiveTriviaSyntax> parseElseDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                        SharedPtr<SyntaxToken> keyword,
                                                        bool isActive,
                                                        bool endIsActive) noexcept;

    SharedPtr<DirectiveTriviaSyntax> parseElseIfDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                          SharedPtr<SyntaxToken> keyword,
                                                          bool isActive,
                                                          bool endIsActive) noexcept;

    SharedPtr<DirectiveTriviaSyntax> parseEndIfDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                         SharedPtr<SyntaxToken> keyword,
                                                         bool isActive,
                                                         bool endIsActive) noexcept;

    SharedPtr<DirectiveTriviaSyntax> parseDefineOrUndefDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                 SharedPtr<SyntaxToken> keyword,
                                                                 bool isActive,
                                                                 bool isFollowingToken) noexcept;

    SharedPtr<DirectiveTriviaSyntax> parseRegionDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                          SharedPtr<SyntaxToken> keyword,
                                                          bool isActive) noexcept;

    SharedPtr<DirectiveTriviaSyntax> parseEndRegionDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                             SharedPtr<SyntaxToken> keyword,
                                                             bool isActive) noexcept;

    SharedPtr<SyntaxToken> parseEndOfDirective() noexcept;
    SharedPtr<ExpressionSyntax> parseExpression() noexcept;
    SharedPtr<ExpressionSyntax> parseLogicalOr() noexcept;
    SharedPtr<ExpressionSyntax> parseLogicalAnd() noexcept;
    SharedPtr<ExpressionSyntax> parseEquality() noexcept;
    SharedPtr<ExpressionSyntax> parseLogicalNot() noexcept;
    SharedPtr<ExpressionSyntax> parsePrimary() noexcept;
    bool evaluateBool(const SharedPtr<ExpressionSyntax>& expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
