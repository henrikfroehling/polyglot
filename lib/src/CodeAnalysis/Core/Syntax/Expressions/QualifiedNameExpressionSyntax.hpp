#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;
class SimpleNameExpressionSyntax;
class SyntaxFactory;

class QualifiedNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                           ISyntaxToken* dotToken,
                                           SimpleNameExpressionSyntax* rightExpression) noexcept;

    virtual ~QualifiedNameExpressionSyntax() noexcept = default;
    inline virtual NameExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual ISyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline virtual SimpleNameExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }
    inline virtual pg_size childCount() const noexcept override { return 3; }
    virtual ISyntaxNode* child(pg_size index) const override;

    static QualifiedNameExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                 NameExpressionSyntax* leftExpression,
                                                 ISyntaxToken* dotToken,
                                                 SimpleNameExpressionSyntax* rightExpression) noexcept;

private:
    NameExpressionSyntax* _pLeftExpression;
    ISyntaxToken* _pDotToken;
    SimpleNameExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
