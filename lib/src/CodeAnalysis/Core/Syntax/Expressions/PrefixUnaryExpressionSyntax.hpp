#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class PrefixUnaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* operatorToken,
                                         ExpressionSyntax* operandExpression) noexcept;

    virtual ~PrefixUnaryExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual ExpressionSyntax* operandExpression() const noexcept { return _pOperandExpression; }

    static PrefixUnaryExpressionSyntax* create(SyntaxKind syntaxKind,
                                               SyntaxToken* operatorToken,
                                               ExpressionSyntax* operandExpression) noexcept;

private:
    SyntaxToken* _pOperatorToken;
    ExpressionSyntax* _pOperandExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
