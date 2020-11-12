#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_QUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API QualifiedNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit QualifiedNameExpressionSyntax(NameExpressionSyntaxPtr leftExpression,
                                           SyntaxTokenPtr dotToken,
                                           SimpleNameExpressionSyntaxPtr rightExpression) noexcept;

    virtual ~QualifiedNameExpressionSyntax() noexcept = default;

private:
    NameExpressionSyntaxPtr _ptrLeftExpression;
    SyntaxTokenPtr _ptrDotToken;
    SimpleNameExpressionSyntaxPtr _ptrRightExpression;
};

using QualifiedNameExpressionSyntaxPtr = std::shared_ptr<QualifiedNameExpressionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_QUALIFIEDNAMEEXPRESSIONSYNTAX_H
