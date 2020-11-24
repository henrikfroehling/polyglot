#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class BinaryExpressionSyntax;
using BinaryExpressionSyntaxPtr = std::shared_ptr<BinaryExpressionSyntax>;

class POLYGLOT_API BinaryExpressionSyntax : public ExpressionSyntax
{
public:
    explicit BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                    ExpressionSyntaxPtr leftExpression,
                                    SyntaxTokenPtr operatorToken,
                                    ExpressionSyntaxPtr rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept = default;
    inline virtual const ExpressionSyntaxPtr& leftExpression() const noexcept { return _ptrLeftExpression; }
    inline virtual const SyntaxTokenPtr& operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual const ExpressionSyntaxPtr& rightExpression() const noexcept { return _ptrRightExpression; }

    static BinaryExpressionSyntaxPtr create(SyntaxKind syntaxKind,
                                            ExpressionSyntaxPtr leftExpression,
                                            SyntaxTokenPtr operatorToken,
                                            ExpressionSyntaxPtr rightExpression) noexcept;

private:
    ExpressionSyntaxPtr _ptrLeftExpression;
    SyntaxTokenPtr _ptrOperatorToken;
    ExpressionSyntaxPtr _ptrRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H
