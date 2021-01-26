#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(LanguageSyntaxToken* usesKeyword,
                                               std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences,
                                               LanguageSyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _pUsesKeyword{usesKeyword},
      _unitReferences{std::move(unitReferences)},
      _pSemiColonToken{semiColonToken}
{}

} // end namespace polyglot::CodeAnalysis
