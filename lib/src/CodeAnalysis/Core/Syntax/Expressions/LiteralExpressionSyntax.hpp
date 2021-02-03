#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     LanguageSyntaxToken* token) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* token() const noexcept { return _pToken; }

    static LiteralExpressionSyntax* create(SyntaxKind syntaxKind,
                                           LanguageSyntaxToken* token) noexcept;

private:
    LanguageSyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
