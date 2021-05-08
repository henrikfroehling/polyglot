#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H

#include "SimpleNameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class IdentifierNameExpressionSyntax : public SimpleNameExpressionSyntax
{
public:
    explicit IdentifierNameExpressionSyntax(ISyntaxToken* identifier) noexcept;
    virtual ~IdentifierNameExpressionSyntax() noexcept = default;
    virtual ISyntaxToken* identifier() const noexcept override { return _pIdentifier; }
    inline virtual pg_size childCount() const noexcept override { return 1; }
    virtual ISyntaxNode* child(pg_size index) const override;

    static IdentifierNameExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                  ISyntaxToken* identifier) noexcept;

protected:
    ISyntaxToken* _pIdentifier;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
