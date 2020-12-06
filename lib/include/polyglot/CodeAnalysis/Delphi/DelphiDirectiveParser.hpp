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

    Ptr<SyntaxNode> parseDirective(bool isActive,
                                   bool endIsActive,
                                   bool isFirstAfterTokenInFile,
                                   bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
    Ptr<DirectiveTriviaSyntax> parseIfDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                Ptr<SyntaxToken> keyword,
                                                bool isActive) noexcept;

    Ptr<DirectiveTriviaSyntax> parseElseDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                  Ptr<SyntaxToken> keyword,
                                                  bool isActive,
                                                  bool endIsActive) noexcept;

    Ptr<DirectiveTriviaSyntax> parseElseIfDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                    Ptr<SyntaxToken> keyword,
                                                    bool isActive,
                                                    bool endIsActive) noexcept;

    Ptr<DirectiveTriviaSyntax> parseEndIfDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                   Ptr<SyntaxToken> keyword,
                                                   bool isActive,
                                                   bool endIsActive) noexcept;

    Ptr<DirectiveTriviaSyntax> parseDefineOrUndefDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                           Ptr<SyntaxToken> keyword,
                                                           bool isActive,
                                                           bool isFollowingToken) noexcept;

    Ptr<DirectiveTriviaSyntax> parseRegionDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                    Ptr<SyntaxToken> keyword,
                                                    bool isActive) noexcept;

    Ptr<DirectiveTriviaSyntax> parseEndRegionDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                       Ptr<SyntaxToken> keyword,
                                                       bool isActive) noexcept;

    Ptr<SyntaxToken> parseEndOfDirective() noexcept;
    Ptr<ExpressionSyntax> parseExpression() noexcept;
    Ptr<ExpressionSyntax> parseLogicalOr() noexcept;
    Ptr<ExpressionSyntax> parseLogicalAnd() noexcept;
    Ptr<ExpressionSyntax> parseEquality() noexcept;
    Ptr<ExpressionSyntax> parseLogicalNot() noexcept;
    Ptr<ExpressionSyntax> parsePrimary() noexcept;
    bool evaluateBool(const Ptr<ExpressionSyntax> expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
