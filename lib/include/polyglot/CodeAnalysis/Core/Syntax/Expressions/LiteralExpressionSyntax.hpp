#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     SyntaxToken* token) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* token() const noexcept { return _pToken; }

    static LiteralExpressionSyntax* create(SyntaxKind syntaxKind,
                                           SyntaxToken* token) noexcept;

private:
    SyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_LITERALEXPRESSIONSYNTAX_H
