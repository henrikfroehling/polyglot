#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H

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
    inline virtual SyntaxToken* openParenthesisToken() const noexcept { return _ptrOpenParenthesisToken; }
    inline virtual ExpressionSyntax* expression() const noexcept { return _ptrExpression; }
    inline virtual SyntaxToken* closeParenthesisToken() const noexcept { return _ptrCloseParenthesisToken; }

    static ParenthesizedExpressionSyntax* create(SyntaxToken* openParenthesisToken,
                                                 ExpressionSyntax* expression,
                                                 SyntaxToken* closeParenthesisToken) noexcept;

private:
    SyntaxToken* _ptrOpenParenthesisToken;
    ExpressionSyntax* _ptrExpression;
    SyntaxToken* _ptrCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
