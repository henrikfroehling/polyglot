#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class PrefixUnaryExpressionSyntax;
using PrefixUnaryExpressionSyntaxPtr = std::shared_ptr<PrefixUnaryExpressionSyntax>;

class POLYGLOT_API PrefixUnaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                         SyntaxTokenPtr operatorToken,
                                         ExpressionSyntaxPtr operandExpression) noexcept;

    virtual ~PrefixUnaryExpressionSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual const ExpressionSyntaxPtr& operandExpression() const noexcept { return _ptrOperandExpression; }

    static PrefixUnaryExpressionSyntaxPtr create(SyntaxKind syntaxKind,
                                                 SyntaxTokenPtr operatorToken,
                                                 ExpressionSyntaxPtr operandExpression) noexcept;

private:
    SyntaxTokenPtr _ptrOperatorToken;
    ExpressionSyntaxPtr _ptrOperandExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H
