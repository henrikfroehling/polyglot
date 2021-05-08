#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class CallExpressionSyntax : public ExpressionSyntax
{
public:
    explicit CallExpressionSyntax(SyntaxKind syntaxKind,
                                  ISyntaxToken* identifier,
                                  ISyntaxToken* openParenthesisToken,
                                  ExpressionSyntax* argumentExpression,
                                  ISyntaxToken* closeParenthesisToken) noexcept;

    virtual ~CallExpressionSyntax() noexcept = default;
    inline virtual ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual ISyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* argumentExpression() const noexcept { return _pArgumentExpression; }
    inline virtual ISyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }
    inline virtual pg_size childCount() const noexcept override { return 4; }
    virtual ISyntaxNode* child(pg_size index) const override;

    static CallExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                        SyntaxKind syntaxKind,
                                        ISyntaxToken* identifier,
                                        ISyntaxToken* openParenthesisToken,
                                        ExpressionSyntax* argumentExpression,
                                        ISyntaxToken* closeParenthesisToken) noexcept;

private:
    ISyntaxToken* _pIdentifier;
    ISyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pArgumentExpression;
    ISyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
