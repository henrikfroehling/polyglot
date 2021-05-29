#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPREFIXUNARYEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPREFIXUNARYEXPRESSIONSYNTAX_H

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

class DelphiPrefixUnaryExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiPrefixUnaryExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                               Core::Syntax::ISyntaxToken* operatorToken,
                                               DelphiExpressionSyntax* operandExpression) noexcept;

    virtual ~DelphiPrefixUnaryExpressionSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* operatorToken() const noexcept { return _pOperatorToken; }
    inline virtual DelphiExpressionSyntax* operandExpression() const noexcept { return _pOperandExpression; }
    inline pg_size childCount() const noexcept override final { return 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pOperatorToken); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pOperandExpression); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiPrefixUnaryExpressionSyntax"; }

    static DelphiPrefixUnaryExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                     Core::Syntax::SyntaxKind syntaxKind,
                                                     Core::Syntax::ISyntaxToken* operatorToken,
                                                     DelphiExpressionSyntax* operandExpression) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pOperatorToken;
    DelphiExpressionSyntax* _pOperandExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPREFIXUNARYEXPRESSIONSYNTAX_H
