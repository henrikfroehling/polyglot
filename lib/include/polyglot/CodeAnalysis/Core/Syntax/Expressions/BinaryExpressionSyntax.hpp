#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API BinaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                    SharedPtr<ExpressionSyntax> leftExpression,
                                    SharedPtr<SyntaxToken> operatorToken,
                                    SharedPtr<ExpressionSyntax> rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept = default;
    inline virtual const SharedPtr<ExpressionSyntax>& leftExpression() const noexcept { return _ptrLeftExpression; }
    inline virtual const SharedPtr<SyntaxToken>& operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual const SharedPtr<ExpressionSyntax>& rightExpression() const noexcept { return _ptrRightExpression; }

    static SharedPtr<BinaryExpressionSyntax> create(SyntaxKind syntaxKind,
                                                    SharedPtr<ExpressionSyntax> leftExpression,
                                                    SharedPtr<SyntaxToken> operatorToken,
                                                    SharedPtr<ExpressionSyntax> rightExpression) noexcept;

private:
    SharedPtr<ExpressionSyntax> _ptrLeftExpression;
    SharedPtr<SyntaxToken> _ptrOperatorToken;
    SharedPtr<ExpressionSyntax> _ptrRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H
