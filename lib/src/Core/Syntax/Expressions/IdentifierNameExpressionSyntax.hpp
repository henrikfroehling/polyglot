#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class IdentifierNameExpressionSyntax : public SimpleNameExpressionSyntax
{
public:
    explicit IdentifierNameExpressionSyntax(ISyntaxToken* identifier) noexcept;
    virtual ~IdentifierNameExpressionSyntax() noexcept {}
    virtual ISyntaxToken* identifier() const noexcept override { return _pIdentifier; }
    inline pg_size childCount() const noexcept override final { return 1; }
    SyntaxVariant child(pg_size index) const override final;
    inline virtual SyntaxVariant first() const noexcept override { return SyntaxVariant::asToken(_pIdentifier); }
    inline virtual SyntaxVariant last() const noexcept override { return SyntaxVariant::asToken(_pIdentifier); }

    virtual std::string typeName() const noexcept override { return "IdentifierNameExpressionSyntax"; }

    static IdentifierNameExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                  ISyntaxToken* identifier) noexcept;

protected:
    ISyntaxToken* _pIdentifier;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
