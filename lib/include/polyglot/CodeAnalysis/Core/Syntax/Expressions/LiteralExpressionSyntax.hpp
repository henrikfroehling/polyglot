#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     SyntaxToken* token) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* token() const noexcept { return _ptrToken; }

    static LiteralExpressionSyntax* create(SyntaxKind syntaxKind,
                                           SyntaxToken* token) noexcept;

private:
    SyntaxToken* _ptrToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H
