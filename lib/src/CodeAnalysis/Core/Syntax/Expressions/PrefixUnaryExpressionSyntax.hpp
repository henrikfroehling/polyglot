#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class PrefixUnaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* operatorToken,
                                         ExpressionSyntax* operandExpression) noexcept;

    virtual ~PrefixUnaryExpressionSyntax() noexcept = default;
    inline virtual ISyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual ExpressionSyntax* operandExpression() const noexcept { return _pOperandExpression; }
    inline virtual pg_size childCount() const noexcept override { return 2; }
    virtual ISyntaxNode* child(pg_size index) const override;

    static PrefixUnaryExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                               SyntaxKind syntaxKind,
                                               ISyntaxToken* operatorToken,
                                               ExpressionSyntax* operandExpression) noexcept;

private:
    ISyntaxToken* _pOperatorToken;
    ExpressionSyntax* _pOperandExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
