#include "Delphi/Syntax/Expressions/DelphiExtendedIdentifierNameSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiExtendedIdentifierNameSyntax::DelphiExtendedIdentifierNameSyntax(Core::Syntax::ISyntaxToken* ampersandToken,
                                                                       Core::Syntax::ISyntaxToken* reservedKeyword) noexcept
    : DelphiSimpleNameSyntax{SyntaxKind::ExtendedIdentifierName},
      _pAmpersandToken{ampersandToken},
      _pReservedKeyword{reservedKeyword}
{}

DelphiExtendedIdentifierNameSyntax* DelphiExtendedIdentifierNameSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                               Core::Syntax::ISyntaxToken* ampersandToken,
                                                                               Core::Syntax::ISyntaxToken* reservedKeyword) noexcept
{
    assert(ampersandToken != nullptr);
    assert(ampersandToken->syntaxKind() == SyntaxKind::AmpersandToken);
    assert(reservedKeyword != nullptr);
    assert(DelphiSyntaxFacts::isReservedWord(reservedKeyword->syntaxKind()));

    auto ptrExtendedIdentifierName = std::make_unique<DelphiExtendedIdentifierNameSyntax>(ampersandToken, reservedKeyword);
    return static_cast<DelphiExtendedIdentifierNameSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExtendedIdentifierName)));
}

} // end namespace polyglot::Delphi::Syntax
