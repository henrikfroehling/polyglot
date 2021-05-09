#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
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
    SyntaxNodeOrToken child(pg_size index) const override final;

    static LiteralExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                           SyntaxKind syntaxKind,
                                           ISyntaxToken* literal) noexcept;

private:
    ISyntaxToken* _pLiteral;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
