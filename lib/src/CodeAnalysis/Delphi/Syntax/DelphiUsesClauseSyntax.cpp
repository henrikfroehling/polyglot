#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(SyntaxTokenPtr usesKeyword,
                                               std::vector<DelphiUnitReferenceDeclarationSyntaxPtr> unitReferences,
                                               SyntaxTokenPtr semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _ptrUsesKeyword{std::move(usesKeyword)},
      _unitReferences{std::move(unitReferences)},
      _ptrSemiColonToken{std::move(semiColonToken)}
{}

} // end namespace polyglot::CodeAnalysis
