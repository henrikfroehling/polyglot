#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class ParenthesizedExpressionSyntax : public ExpressionSyntax
{
public:
    explicit ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                           LanguageSyntaxToken* openParenthesisToken,
                                           ExpressionSyntax* expression,
                                           LanguageSyntaxToken* closeParenthesisToken) noexcept;

    virtual ~ParenthesizedExpressionSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline virtual LanguageSyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }

    static ParenthesizedExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                 LanguageSyntaxToken* openParenthesisToken,
                                                 ExpressionSyntax* expression,
                                                 LanguageSyntaxToken* closeParenthesisToken) noexcept;

private:
    LanguageSyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pExpression;
    LanguageSyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
