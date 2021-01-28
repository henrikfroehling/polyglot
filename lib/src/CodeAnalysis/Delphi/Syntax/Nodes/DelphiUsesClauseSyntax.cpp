#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(LanguageSyntaxToken* usesKeyword,
                                               std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences,
                                               LanguageSyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _pUsesKeyword{usesKeyword},
      _unitReferences{std::move(unitReferences)},
      _pSemiColonToken{semiColonToken}
{
    adjustWidthAndFlags(_pUsesKeyword);

    for (DelphiUnitReferenceDeclarationSyntax* referenceNode : _unitReferences)
        adjustWidthAndFlags(referenceNode);

    adjustWidthAndFlags(_pSemiColonToken);
}

} // end namespace polyglot::CodeAnalysis
