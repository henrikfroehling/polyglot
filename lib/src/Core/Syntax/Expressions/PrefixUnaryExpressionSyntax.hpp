#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
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

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
