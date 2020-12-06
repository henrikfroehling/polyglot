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
                                           Ptr<SyntaxToken> openParenthesisToken,
                                           Ptr<ExpressionSyntax> expression,
                                           Ptr<SyntaxToken> closeParenthesisToken) noexcept;

    virtual ~ParenthesizedExpressionSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> openParenthesisToken() const noexcept { return _ptrOpenParenthesisToken; }
    inline virtual const Ptr<ExpressionSyntax> expression() const noexcept { return _ptrExpression; }
    inline virtual const Ptr<SyntaxToken> closeParenthesisToken() const noexcept { return _ptrCloseParenthesisToken; }

    static Ptr<ParenthesizedExpressionSyntax> create(Ptr<SyntaxToken> openParenthesisToken,
                                                     Ptr<ExpressionSyntax> expression,
                                                     Ptr<SyntaxToken> closeParenthesisToken) noexcept;

private:
    Ptr<SyntaxToken> _ptrOpenParenthesisToken;
    Ptr<ExpressionSyntax> _ptrExpression;
    Ptr<SyntaxToken> _ptrCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_PARENTHESIZEDEXPRESSIONSYNTAX_H
