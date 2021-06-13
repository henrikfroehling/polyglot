#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHILITERALEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHILITERALEXPRESSIONSYNTAX_H

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

class DelphiLiteralExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiLiteralExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                           Core::Syntax::ISyntaxToken* literal) noexcept;

    virtual ~DelphiLiteralExpressionSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* token() const noexcept { return _pLiteral; }
    inline pg_size childCount() const noexcept override final { return 1; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pLiteral); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pLiteral); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiLiteralExpressionSyntax"; }

    static DelphiLiteralExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::SyntaxKind syntaxKind,
                                                 Core::Syntax::ISyntaxToken* literal) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pLiteral;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHILITERALEXPRESSIONSYNTAX_H
