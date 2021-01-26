#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class CallExpressionSyntax : public ExpressionSyntax
{
public:
    explicit CallExpressionSyntax(SyntaxKind syntaxKind,
                                  LanguageSyntaxToken* identifier,
                                  LanguageSyntaxToken* openParenthesisToken,
                                  ExpressionSyntax* argumentExpression,
                                  LanguageSyntaxToken* closeParenthesisToken) noexcept;

    virtual ~CallExpressionSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual LanguageSyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual ExpressionSyntax* argumentExpression() const noexcept { return _pArgumentExpression; }
    inline virtual LanguageSyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }

    static CallExpressionSyntax* create(SyntaxKind syntaxKind,
                                        LanguageSyntaxToken* identifier,
                                        LanguageSyntaxToken* openParenthesisToken,
                                        ExpressionSyntax* argumentExpression,
                                        LanguageSyntaxToken* closeParenthesisToken) noexcept;

private:
    LanguageSyntaxToken* _pIdentifier;
    LanguageSyntaxToken* _pOpenParenthesisToken;
    ExpressionSyntax* _pArgumentExpression;
    LanguageSyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_CALLEXPRESSIONSYNTAX_H
