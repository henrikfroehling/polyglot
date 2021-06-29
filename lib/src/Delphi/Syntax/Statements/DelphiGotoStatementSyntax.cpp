#include "Delphi/Syntax/Statements/DelphiGotoStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiGotoStatementSyntax::DelphiGotoStatementSyntax(ISyntaxToken* gotoKeyword,
                                                     ISyntaxToken* labelToken,
                                                     ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::GotoStatement},
      _pGotoKeyword{gotoKeyword},
      _pLabelToken{labelToken},
      _pSemiColonToken{semiColonToken}
{
    _position = _pGotoKeyword->position();
    adjustWidthAndFlags(_pGotoKeyword);
    adjustWidthAndFlags(_pLabelToken);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiGotoStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pGotoKeyword);
        case 1: return SyntaxVariant::asToken(_pLabelToken);
        case 2: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiGotoStatementSyntax* DelphiGotoStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* gotoKeyword,
                                                             ISyntaxToken* labelToken,
                                                             ISyntaxToken* semiColonToken) noexcept
{
    assert(gotoKeyword != nullptr);
    assert(gotoKeyword->syntaxKind() == SyntaxKind::GotoKeyword);
    assert(labelToken != nullptr);
    const SyntaxKind labelSyntaxKind = labelToken->syntaxKind();
    assert(labelSyntaxKind == SyntaxKind::IdentifierToken || labelSyntaxKind == SyntaxKind::IntegerNumberLiteralToken);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrGotoStatementSyntax = std::make_unique<DelphiGotoStatementSyntax>(gotoKeyword, labelToken, semiColonToken);
    return static_cast<DelphiGotoStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrGotoStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
