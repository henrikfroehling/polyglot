#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class ParenthesizedExpressionSyntax : public ExpressionSyntax
{
public:
    explicit ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                           ISyntaxToken* openParenthesisToken,
                                           ExpressionSyntax* expression,
                                           ISyntaxToken* closeParenthesisToken) noexcept;

    virtual ~ParenthesizedExpressionSyntax() noexcept {}
    inline virtual ISyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline virtual ISyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }
    inline pg_size childCount() const noexcept override final { return 3; }
    SyntaxVariant child(pg_size index) const override final;
    inline virtual ISyntaxToken* firstToken() const noexcept override { return _pOpenParenthesisToken; }
    inline virtual ISyntaxToken* lastToken() const noexcept override { return _pCloseParenthesisToken; }

    static ParenthesizedExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                 ISyntaxToken* openParenthesisToken,
                                                 ExpressionSyntax* expression,
                                                 ISyntaxToken* closeParenthesisToken) noexcept;

private:
    ISyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pExpression;
    ISyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
