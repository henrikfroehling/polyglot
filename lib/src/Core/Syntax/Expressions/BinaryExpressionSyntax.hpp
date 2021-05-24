#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class BinaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                    ExpressionSyntax* leftExpression,
                                    ISyntaxToken* operatorToken,
                                    ExpressionSyntax* rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept {}
    inline virtual ExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual ISyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual ExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }
    inline pg_size childCount() const noexcept override final { return 3; }
    SyntaxVariant child(pg_size index) const override final;
    inline virtual SyntaxVariant first() const noexcept override { return SyntaxVariant::asNode(_pLeftExpression); }
    inline virtual SyntaxVariant last() const noexcept override { return SyntaxVariant::asNode(_pRightExpression); }

    inline virtual pg_string typeName() const noexcept override { return L"BinaryExpressionSyntax"; }

    static BinaryExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                          SyntaxKind syntaxKind,
                                          ExpressionSyntax* leftExpression,
                                          ISyntaxToken* operatorToken,
                                          ExpressionSyntax* rightExpression) noexcept;

private:
    ExpressionSyntax* _pLeftExpression;
    ISyntaxToken* _pOperatorToken;
    ExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H
