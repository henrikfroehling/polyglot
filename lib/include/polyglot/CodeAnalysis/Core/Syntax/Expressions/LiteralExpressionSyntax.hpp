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
                                     SharedPtr<SyntaxToken> token) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& token() const noexcept { return _ptrToken; }

    static SharedPtr<LiteralExpressionSyntax> create(SyntaxKind syntaxKind,
                                                     SharedPtr<SyntaxToken> token) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H
