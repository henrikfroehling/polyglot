#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API IdentifierNameExpressionSyntax : public SimpleNameExpressionSyntax
{
public:
    explicit IdentifierNameExpressionSyntax(SyntaxToken* identifier) noexcept;
    virtual ~IdentifierNameExpressionSyntax() noexcept = default;
    virtual SyntaxToken* identifier() const noexcept override { return _pIdentifier; }

    static IdentifierNameExpressionSyntax* create(SyntaxToken* identifier) noexcept;

protected:
    SyntaxToken* _pIdentifier;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
