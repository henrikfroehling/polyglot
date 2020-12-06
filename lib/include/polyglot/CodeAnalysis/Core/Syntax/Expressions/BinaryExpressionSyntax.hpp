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
                                    Ptr<ExpressionSyntax> leftExpression,
                                    Ptr<SyntaxToken> operatorToken,
                                    Ptr<ExpressionSyntax> rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept = default;
    inline virtual const Ptr<ExpressionSyntax>& leftExpression() const noexcept { return _ptrLeftExpression; }
    inline virtual const Ptr<SyntaxToken>& operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual const Ptr<ExpressionSyntax>& rightExpression() const noexcept { return _ptrRightExpression; }

    static Ptr<BinaryExpressionSyntax> create(SyntaxKind syntaxKind,
                                              Ptr<ExpressionSyntax> leftExpression,
                                              Ptr<SyntaxToken> operatorToken,
                                              Ptr<ExpressionSyntax> rightExpression) noexcept;

private:
    Ptr<ExpressionSyntax> _ptrLeftExpression;
    Ptr<SyntaxToken> _ptrOperatorToken;
    Ptr<ExpressionSyntax> _ptrRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H
