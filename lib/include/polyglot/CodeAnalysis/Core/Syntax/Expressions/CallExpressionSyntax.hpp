#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API CallExpressionSyntax : public ExpressionSyntax
{
public:
    explicit CallExpressionSyntax(SyntaxKind syntaxKind,
                                  SyntaxToken* identifier,
                                  SyntaxToken* openParenthesisToken,
                                  ExpressionSyntax* argumentExpression,
                                  SyntaxToken* closeParenthesisToken) noexcept;

    virtual ~CallExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* identifier() const noexcept { return _ptrIdentifier; }
    inline virtual SyntaxToken* openParenthesisToken() const noexcept { return _ptrOpenParenthesisToken; }
    inline virtual ExpressionSyntax* argumentExpression() const noexcept { return _ptrArgumentExpression; }
    inline virtual SyntaxToken* closeParenthesisToken() const noexcept { return _ptrCloseParenthesisToken; }

    static CallExpressionSyntax* create(SyntaxKind syntaxKind,
                                        SyntaxToken* identifier,
                                        SyntaxToken* openParenthesisToken,
                                        ExpressionSyntax* argumentExpression,
                                        SyntaxToken* closeParenthesisToken) noexcept;

private:
    SyntaxToken* _ptrIdentifier;
    SyntaxToken* _ptrOpenParenthesisToken;
    ExpressionSyntax* _ptrArgumentExpression;
    SyntaxToken* _ptrCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
