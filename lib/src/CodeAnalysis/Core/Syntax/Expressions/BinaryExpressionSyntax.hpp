#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SyntaxFactory;

class BinaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                    ExpressionSyntax* leftExpression,
                                    LanguageSyntaxToken* operatorToken,
                                    ExpressionSyntax* rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept = default;
    inline virtual ExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual LanguageSyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual ExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }
    virtual LanguageSyntaxNode* child(pg_size index) const override;
    inline virtual pg_size childCount() const noexcept override { return 3; }

    static BinaryExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                          SyntaxKind syntaxKind,
                                          ExpressionSyntax* leftExpression,
                                          LanguageSyntaxToken* operatorToken,
                                          ExpressionSyntax* rightExpression) noexcept;

private:
    ExpressionSyntax* _pLeftExpression;
    LanguageSyntaxToken* _pOperatorToken;
    ExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_BINARYEXPRESSIONSYNTAX_H
