#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class SimpleNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit SimpleNameExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~SimpleNameExpressionSyntax() noexcept = default;
    virtual LanguageSyntaxToken* identifier() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H
