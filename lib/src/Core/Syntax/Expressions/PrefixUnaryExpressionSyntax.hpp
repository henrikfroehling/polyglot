#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PREFIXUNARYEXPRESSIONSYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
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

    virtual ~PrefixUnaryExpressionSyntax() noexcept {}
    inline virtual ISyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual ExpressionSyntax* operandExpression() const noexcept { return _pOperandExpression; }
    inline pg_size childCount() const noexcept override final { return 2; }
    SyntaxVariant child(pg_size index) const override final;
    inline virtual SyntaxVariant first() const noexcept override { return SyntaxVariant::asToken(_pOperatorToken); }
    inline virtual SyntaxVariant last() const noexcept override { return SyntaxVariant::asNode(_pOperandExpression); }

    virtual std::string typeName() const noexcept override { return "PrefixUnaryExpressionSyntax"; }

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
