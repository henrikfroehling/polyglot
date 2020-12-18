#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(SyntaxToken* usesKeyword,
                                               std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences,
                                               SyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _pUsesKeyword{usesKeyword},
      _unitReferences{std::move(unitReferences)},
      _pSemiColonToken{semiColonToken}
{}

} // end namespace polyglot::CodeAnalysis
