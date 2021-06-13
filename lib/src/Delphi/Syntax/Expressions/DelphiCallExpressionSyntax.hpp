#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHICALLEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHICALLEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCallExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiCallExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                        Core::Syntax::ISyntaxToken* identifier,
                                        Core::Syntax::ISyntaxToken* openParenthesisToken,
                                        DelphiExpressionSyntax* argumentExpression,
                                        Core::Syntax::ISyntaxToken* closeParenthesisToken) noexcept;

    virtual ~DelphiCallExpressionSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual Core::Syntax::ISyntaxToken* openParenthesisToken() const noexcept { return _pOpenParenthesisToken; }
    inline virtual DelphiExpressionSyntax* argumentExpression() const noexcept { return _pArgumentExpression; }
    inline virtual Core::Syntax::ISyntaxToken* closeParenthesisToken() const noexcept { return _pCloseParenthesisToken; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pIdentifier); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pCloseParenthesisToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiCallExpressionSyntax"; }

    static DelphiCallExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::SyntaxKind syntaxKind,
                                              Core::Syntax::ISyntaxToken* identifier,
                                              Core::Syntax::ISyntaxToken* openParenthesisToken,
                                              DelphiExpressionSyntax* argumentExpression,
                                              Core::Syntax::ISyntaxToken* closeParenthesisToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pIdentifier;
    Core::Syntax::ISyntaxToken* _pOpenParenthesisToken;
    DelphiExpressionSyntax* _pArgumentExpression;
    Core::Syntax::ISyntaxToken* _pCloseParenthesisToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHICALLEXPRESSIONSYNTAX_H
