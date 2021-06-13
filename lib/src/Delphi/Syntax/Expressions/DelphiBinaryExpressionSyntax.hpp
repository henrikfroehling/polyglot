#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIBINARYEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIBINARYEXPRESSIONSYNTAX_H

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

class DelphiBinaryExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiBinaryExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                          DelphiExpressionSyntax* leftExpression,
                                          Core::Syntax::ISyntaxToken* operatorToken,
                                          DelphiExpressionSyntax* rightExpression) noexcept;

    virtual ~DelphiBinaryExpressionSyntax() noexcept {}
    inline virtual DelphiExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual Core::Syntax::ISyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual DelphiExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pLeftExpression); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pRightExpression); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiBinaryExpressionSyntax"; }

    static DelphiBinaryExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                Core::Syntax::SyntaxKind syntaxKind,
                                                DelphiExpressionSyntax* leftExpression,
                                                Core::Syntax::ISyntaxToken* operatorToken,
                                                DelphiExpressionSyntax* rightExpression) noexcept;

private:
    DelphiExpressionSyntax* _pLeftExpression;
    Core::Syntax::ISyntaxToken* _pOperatorToken;
    DelphiExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIBINARYEXPRESSIONSYNTAX_H
