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
                                         Ptr<SyntaxToken> operatorToken,
                                         Ptr<ExpressionSyntax> operandExpression) noexcept;

    virtual ~PrefixUnaryExpressionSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual const Ptr<ExpressionSyntax> operandExpression() const noexcept { return _ptrOperandExpression; }

    static Ptr<PrefixUnaryExpressionSyntax> create(SyntaxKind syntaxKind,
                                                   Ptr<SyntaxToken> operatorToken,
                                                   Ptr<ExpressionSyntax> operandExpression) noexcept;

private:
    Ptr<SyntaxToken> _ptrOperatorToken;
    Ptr<ExpressionSyntax> _ptrOperandExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PREFIXUNARYEXPRESSIONSYNTAX_H
