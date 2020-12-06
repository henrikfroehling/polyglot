#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_QUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API QualifiedNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit QualifiedNameExpressionSyntax(Ptr<NameExpressionSyntax> leftExpression,
                                           Ptr<SyntaxToken> dotToken,
                                           Ptr<SimpleNameExpressionSyntax> rightExpression) noexcept;

    virtual ~QualifiedNameExpressionSyntax() noexcept = default;

private:
    Ptr<NameExpressionSyntax> _ptrLeftExpression;
    Ptr<SyntaxToken> _ptrDotToken;
    Ptr<SimpleNameExpressionSyntax> _ptrRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
