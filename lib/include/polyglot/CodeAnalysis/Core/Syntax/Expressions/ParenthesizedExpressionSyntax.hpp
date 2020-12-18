#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API ParenthesizedExpressionSyntax : public ExpressionSyntax
{
public:
    explicit ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                           SyntaxToken* openParenthesisToken,
                                           ExpressionSyntax* expression,
                                           SyntaxToken* closeParenthesisToken) noexcept;

    virtual ~ParenthesizedExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline virtual SyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }

    static ParenthesizedExpressionSyntax* create(SyntaxToken* openParenthesisToken,
                                                 ExpressionSyntax* expression,
                                                 SyntaxToken* closeParenthesisToken) noexcept;

private:
    SyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pExpression;
    SyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
