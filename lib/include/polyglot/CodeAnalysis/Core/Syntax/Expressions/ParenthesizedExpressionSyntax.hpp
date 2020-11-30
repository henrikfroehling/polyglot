#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ParenthesizedExpressionSyntax : public ExpressionSyntax
{
public:
    explicit ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                           SharedPtr<SyntaxToken> openParenthesisToken,
                                           SharedPtr<ExpressionSyntax> expression,
                                           SharedPtr<SyntaxToken> closeParenthesisToken) noexcept;

    virtual ~ParenthesizedExpressionSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& openParenthesisToken() const noexcept { return _ptrOpenParenthesisToken; }
    inline virtual const SharedPtr<ExpressionSyntax>& expression() const noexcept { return _ptrExpression; }
    inline virtual const SharedPtr<SyntaxToken>& closeParenthesisToken() const noexcept { return _ptrCloseParenthesisToken; }

    static SharedPtr<ParenthesizedExpressionSyntax> create(SharedPtr<SyntaxToken> openParenthesisToken,
                                                           SharedPtr<ExpressionSyntax> expression,
                                                           SharedPtr<SyntaxToken> closeParenthesisToken) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrOpenParenthesisToken;
    SharedPtr<ExpressionSyntax> _ptrExpression;
    SharedPtr<SyntaxToken> _ptrCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
