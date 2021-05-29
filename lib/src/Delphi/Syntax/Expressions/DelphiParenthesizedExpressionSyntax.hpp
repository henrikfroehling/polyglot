#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPARENTHESIZEDEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPARENTHESIZEDEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiParenthesizedExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiParenthesizedExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                                 Core::Syntax::ISyntaxToken* openParenthesisToken,
                                                 DelphiExpressionSyntax* expression,
                                                 Core::Syntax::ISyntaxToken* closeParenthesisToken) noexcept;

    virtual ~DelphiParenthesizedExpressionSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline virtual Core::Syntax::ISyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pOpenParenthesisToken); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pCloseParenthesisToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiParenthesizedExpressionSyntax"; }

    static DelphiParenthesizedExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                       Core::Syntax::ISyntaxToken* openParenthesisToken,
                                                       DelphiExpressionSyntax* expression,
                                                       Core::Syntax::ISyntaxToken* closeParenthesisToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pOpenParenthesisToken;
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPARENTHESIZEDEXPRESSIONSYNTAX_H
