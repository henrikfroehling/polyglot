#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class ParenthesizedExpressionSyntax;
using ParenthesizedExpressionSyntaxPtr = std::shared_ptr<ParenthesizedExpressionSyntax>;

class POLYGLOT_API ParenthesizedExpressionSyntax : public ExpressionSyntax
{
public:
    explicit ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                           SyntaxTokenPtr openParenthesisToken,
                                           ExpressionSyntaxPtr expression,
                                           SyntaxTokenPtr closeParenthesisToken) noexcept;

    virtual ~ParenthesizedExpressionSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& openParenthesisToken() const noexcept { return _ptrOpenParenthesisToken; }
    inline virtual const ExpressionSyntaxPtr& expression() const noexcept { return _ptrExpression; }
    inline virtual const SyntaxTokenPtr& closeParenthesisToken() const noexcept { return _ptrCloseParenthesisToken; }

    static ParenthesizedExpressionSyntaxPtr Create(SyntaxTokenPtr openParenthesisToken,
                                                   ExpressionSyntaxPtr expression,
                                                   SyntaxTokenPtr closeParenthesisToken) noexcept;

private:
    SyntaxTokenPtr _ptrOpenParenthesisToken;
    ExpressionSyntaxPtr _ptrExpression;
    SyntaxTokenPtr _ptrCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
