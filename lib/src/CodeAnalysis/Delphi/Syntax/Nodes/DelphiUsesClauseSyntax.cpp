#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(SharedPtr<SyntaxToken> usesKeyword,
                                               std::vector<SharedPtr<DelphiUnitReferenceDeclarationSyntax>> unitReferences,
                                               SharedPtr<SyntaxToken> semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _ptrUsesKeyword{std::move(usesKeyword)},
      _unitReferences{std::move(unitReferences)},
      _ptrSemiColonToken{std::move(semiColonToken)}
{}

} // end namespace polyglot::CodeAnalysis
