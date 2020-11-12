#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class LiteralExpressionSyntax;
using LiteralExpressionSyntaxPtr = std::shared_ptr<LiteralExpressionSyntax>;

class POLYGLOT_API LiteralExpressionSyntax : public ExpressionSyntax
{
public:
    explicit LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                     SyntaxTokenPtr token) noexcept;

    virtual ~LiteralExpressionSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& token() const noexcept { return _ptrToken; }

    static LiteralExpressionSyntaxPtr Create(SyntaxKind syntaxKind,
                                             SyntaxTokenPtr token) noexcept;

private:
    SyntaxTokenPtr _ptrToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LITERALEXPRESSIONSYNTAX_H
