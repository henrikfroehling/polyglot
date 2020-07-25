#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSimpleNameSyntax::DelphiSimpleNameSyntax(SyntaxKind syntaxKind,
                                               std::shared_ptr<SyntaxToken> identifier) noexcept
    : DelphiNameSyntax{syntaxKind},
      _ptrIdentifier{std::move(identifier)}
{}

} // end namespace polyglot::CodeAnalysis
