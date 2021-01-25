#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class BinaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                    ExpressionSyntax* leftExpression,
                                    SyntaxToken* operatorToken,
                                    ExpressionSyntax* rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept = default;
    inline virtual ExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual SyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual ExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }

    static BinaryExpressionSyntax* create(SyntaxKind syntaxKind,
                                          ExpressionSyntax* leftExpression,
                                          SyntaxToken* operatorToken,
                                          ExpressionSyntax* rightExpression) noexcept;

private:
    ExpressionSyntax* _pLeftExpression;
    SyntaxToken* _pOperatorToken;
    ExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H
