#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SimpleNameExpressionSyntax;
class SyntaxFactory;

class QualifiedNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                           LanguageSyntaxToken* dotToken,
                                           SimpleNameExpressionSyntax* rightExpression) noexcept;

    virtual ~QualifiedNameExpressionSyntax() noexcept = default;
    inline virtual NameExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual LanguageSyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline virtual SimpleNameExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }
    virtual LanguageSyntaxNode* child(pg_size index) const override;
    inline virtual pg_size childCount() const noexcept override { return 3; }

    static QualifiedNameExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                 NameExpressionSyntax* leftExpression,
                                                 LanguageSyntaxToken* dotToken,
                                                 SimpleNameExpressionSyntax* rightExpression) noexcept;

private:
    NameExpressionSyntax* _pLeftExpression;
    LanguageSyntaxToken* _pDotToken;
    SimpleNameExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
