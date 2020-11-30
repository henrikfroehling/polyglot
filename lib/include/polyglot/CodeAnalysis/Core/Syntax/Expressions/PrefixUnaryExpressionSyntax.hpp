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
                                         SharedPtr<SyntaxToken> operatorToken,
                                         SharedPtr<ExpressionSyntax> operandExpression) noexcept;

    virtual ~PrefixUnaryExpressionSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual const SharedPtr<ExpressionSyntax>& operandExpression() const noexcept { return _ptrOperandExpression; }

    static SharedPtr<PrefixUnaryExpressionSyntax> create(SyntaxKind syntaxKind,
                                                         SharedPtr<SyntaxToken> operatorToken,
                                                         SharedPtr<ExpressionSyntax> operandExpression) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrOperatorToken;
    SharedPtr<ExpressionSyntax> _ptrOperandExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H
