#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
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

    virtual ~ParenthesizedExpressionSyntax() noexcept = default;
    inline virtual ISyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline virtual ISyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }
    inline virtual pg_size childCount() const noexcept override { return 3; }
    virtual ISyntaxNode* child(pg_size index) const override;

    static ParenthesizedExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                 ISyntaxToken* openParenthesisToken,
                                                 ExpressionSyntax* expression,
                                                 ISyntaxToken* closeParenthesisToken) noexcept;

private:
    ISyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pExpression;
    ISyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_PARENTHESIZEDEXPRESSIONSYNTAX_H
