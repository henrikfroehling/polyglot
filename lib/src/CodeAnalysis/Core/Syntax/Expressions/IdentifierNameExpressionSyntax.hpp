#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H

#include "CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class IdentifierNameExpressionSyntax : public SimpleNameExpressionSyntax
{
public:
    explicit IdentifierNameExpressionSyntax(LanguageSyntaxToken* identifier) noexcept;
    virtual ~IdentifierNameExpressionSyntax() noexcept = default;
    virtual LanguageSyntaxToken* identifier() const noexcept override { return _pIdentifier; }

    static IdentifierNameExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                  LanguageSyntaxToken* identifier) noexcept;

protected:
    LanguageSyntaxToken* _pIdentifier;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
