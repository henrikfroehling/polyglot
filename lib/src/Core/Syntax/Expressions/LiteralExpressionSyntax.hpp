#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     ISyntaxToken* literal) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept {}
    inline virtual ISyntaxToken* token() const noexcept { return _pLiteral; }
    inline pg_size childCount() const noexcept override final { return 1; }
    SyntaxVariant child(pg_size index) const override final;
    inline virtual SyntaxVariant first() const noexcept override { return SyntaxVariant::asToken(_pLiteral); }
    inline virtual SyntaxVariant last() const noexcept override { return SyntaxVariant::asToken(_pLiteral); }

    virtual pg_string typeName() const noexcept override { return L"LiteralExpressionSyntax"; }

    static LiteralExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                           SyntaxKind syntaxKind,
                                           ISyntaxToken* literal) noexcept;

private:
    ISyntaxToken* _pLiteral;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
