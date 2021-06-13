#include "Delphi/Syntax/Expressions/DelphiExtendedIdentifierNameSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiExtendedIdentifierNameSyntax::DelphiExtendedIdentifierNameSyntax(ISyntaxToken* ampersandToken,
                                                                       ISyntaxToken* reservedKeyword) noexcept
    : DelphiSimpleNameSyntax{SyntaxKind::ExtendedIdentifierName},
      _pAmpersandToken{ampersandToken},
      _pReservedKeyword{reservedKeyword}
{}

SyntaxVariant DelphiExtendedIdentifierNameSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pAmpersandToken);
        case 1: return SyntaxVariant::asToken(_pReservedKeyword);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExtendedIdentifierNameSyntax* DelphiExtendedIdentifierNameSyntax::create(SyntaxFactory& syntaxFactory,
                                                                               ISyntaxToken* ampersandToken,
                                                                               ISyntaxToken* reservedKeyword) noexcept
{
    assert(ampersandToken != nullptr);
    assert(ampersandToken->syntaxKind() == SyntaxKind::AmpersandToken);
    assert(reservedKeyword != nullptr);
    assert(DelphiSyntaxFacts::isReservedWord(reservedKeyword->syntaxKind()));

    auto ptrExtendedIdentifierName = std::make_unique<DelphiExtendedIdentifierNameSyntax>(ampersandToken, reservedKeyword);
    return static_cast<DelphiExtendedIdentifierNameSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExtendedIdentifierName)));
}

} // end namespace polyglot::Delphi::Syntax
