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
                                    ExpressionSyntax* leftExpression,
                                    SyntaxToken* operatorToken,
                                    ExpressionSyntax* rightExpression) noexcept;

    virtual ~BinaryExpressionSyntax() noexcept = default;
    inline virtual ExpressionSyntax* leftExpression() const noexcept { return _ptrLeftExpression; }
    inline virtual SyntaxToken* operatorToken() const noexcept { return _ptrOperatorToken; }
    inline virtual ExpressionSyntax* rightExpression() const noexcept { return _ptrRightExpression; }

    static BinaryExpressionSyntax* create(SyntaxKind syntaxKind,
                                          ExpressionSyntax* leftExpression,
                                          SyntaxToken* operatorToken,
                                          ExpressionSyntax* rightExpression) noexcept;

private:
    ExpressionSyntax* _ptrLeftExpression;
    SyntaxToken* _ptrOperatorToken;
    ExpressionSyntax* _ptrRightExpression;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BINARYEXPRESSIONSYNTAX_H
