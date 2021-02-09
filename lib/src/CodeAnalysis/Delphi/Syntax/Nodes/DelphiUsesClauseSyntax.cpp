#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(LanguageSyntaxToken* usesKeyword,
                                               std::vector<DelphiUnitReferenceDeclarationSyntax*>&& unitReferences,
                                               LanguageSyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _pUsesKeyword{usesKeyword},
      _unitReferences{std::move(unitReferences)},
      _pSemiColonToken{semiColonToken}
{
    _position = _pUsesKeyword->position();
    adjustWidthAndFlags(_pUsesKeyword);

    for (DelphiUnitReferenceDeclarationSyntax* referenceNode : _unitReferences)
        adjustWidthAndFlags(referenceNode);

    adjustWidthAndFlags(_pSemiColonToken);
}

DelphiUsesClauseSyntax* DelphiUsesClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                       LanguageSyntaxToken* usesKeyword,
                                                       std::vector<DelphiUnitReferenceDeclarationSyntax*>&& unitReferences,
                                                       LanguageSyntaxToken* semiColonToken) noexcept
{
    assert(usesKeyword != nullptr);
    assert(usesKeyword->syntaxKind() == SyntaxKind::UsesKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrUsesClauseSyntax = std::make_unique<DelphiUsesClauseSyntax>(usesKeyword, std::move(unitReferences), semiColonToken);
    return static_cast<DelphiUsesClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUsesClauseSyntax)));
}

} // end namespace polyglot::CodeAnalysis
