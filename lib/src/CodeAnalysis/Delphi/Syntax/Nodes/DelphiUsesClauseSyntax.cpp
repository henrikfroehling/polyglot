#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(Ptr<SyntaxToken> usesKeyword,
                                               std::vector<Ptr<DelphiUnitReferenceDeclarationSyntax>> unitReferences,
                                               Ptr<SyntaxToken> semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _ptrUsesKeyword{usesKeyword},
      _unitReferences{std::move(unitReferences)},
      _ptrSemiColonToken{semiColonToken}
{}

} // end namespace polyglot::CodeAnalysis
