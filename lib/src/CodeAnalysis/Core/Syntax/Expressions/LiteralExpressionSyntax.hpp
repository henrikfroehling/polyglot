#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SyntaxFactory;

class LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     LanguageSyntaxToken* token) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* token() const noexcept { return _pToken; }
    virtual LanguageSyntaxNode* child(pg_size index) const override;
    inline virtual pg_size childCount() const noexcept override { return 1; }

    static LiteralExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                           SyntaxKind syntaxKind,
                                           LanguageSyntaxToken* token) noexcept;

private:
    LanguageSyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
