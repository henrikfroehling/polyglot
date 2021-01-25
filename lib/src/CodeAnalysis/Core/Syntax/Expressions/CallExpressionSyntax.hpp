#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class CallExpressionSyntax : public ExpressionSyntax
{
public:
    explicit CallExpressionSyntax(SyntaxKind syntaxKind,
                                  SyntaxToken* identifier,
                                  SyntaxToken* openParenthesisToken,
                                  ExpressionSyntax* argumentExpression,
                                  SyntaxToken* closeParenthesisToken) noexcept;

    virtual ~CallExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual SyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* argumentExpression() const noexcept { return _pArgumentExpression; }
    inline virtual SyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }

    static CallExpressionSyntax* create(SyntaxKind syntaxKind,
                                        SyntaxToken* identifier,
                                        SyntaxToken* openParenthesisToken,
                                        ExpressionSyntax* argumentExpression,
                                        SyntaxToken* closeParenthesisToken) noexcept;

private:
    SyntaxToken* _pIdentifier;
    SyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pArgumentExpression;
    SyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
