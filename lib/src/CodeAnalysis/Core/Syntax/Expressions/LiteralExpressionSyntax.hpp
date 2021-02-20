#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     ISyntaxToken* literal) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual ISyntaxToken* token() const noexcept { return _pLiteral; }
    inline virtual pg_size childCount() const noexcept override { return 1; }
    virtual ISyntaxNode* child(pg_size index) const override;

    static LiteralExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                           SyntaxKind syntaxKind,
                                           ISyntaxToken* literal) noexcept;

private:
    ISyntaxToken* _pLiteral;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
