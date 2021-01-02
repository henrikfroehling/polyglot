#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API SimpleNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit SimpleNameExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~SimpleNameExpressionSyntax() noexcept = default;
    virtual SyntaxToken* identifier() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H
