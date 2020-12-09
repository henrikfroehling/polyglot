#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API PrefixUnaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* operatorToken,
                                         ExpressionSyntax* operandExpression) noexcept;

    virtual ~PrefixUnaryExpressionSyntax() noexcept = default;
    inline virtual SyntaxToken* operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual ExpressionSyntax* operandExpression() const noexcept { return _ptrOperandExpression; }

    static PrefixUnaryExpressionSyntax* create(SyntaxKind syntaxKind,
                                               SyntaxToken* operatorToken,
                                               ExpressionSyntax* operandExpression) noexcept;

private:
    SyntaxToken* _ptrOperatorToken;
    ExpressionSyntax* _ptrOperandExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H
