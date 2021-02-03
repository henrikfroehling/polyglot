#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SimpleNameExpressionSyntax;

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

    static QualifiedNameExpressionSyntax* create(NameExpressionSyntax* leftExpression,
                                                 LanguageSyntaxToken* dotToken,
                                                 SimpleNameExpressionSyntax* rightExpression) noexcept;

private:
    NameExpressionSyntax* _pLeftExpression;
    LanguageSyntaxToken* _pDotToken;
    SimpleNameExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H