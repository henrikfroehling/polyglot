#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;
class SimpleNameExpressionSyntax;

class POLYGLOT_API QualifiedNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                           SyntaxToken* dotToken,
                                           SimpleNameExpressionSyntax* rightExpression) noexcept;

    virtual ~QualifiedNameExpressionSyntax() noexcept = default;
    inline virtual NameExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual SyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline virtual SimpleNameExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }

private:
    NameExpressionSyntax* _pLeftExpression;
    SyntaxToken* _pDotToken;
    SimpleNameExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
