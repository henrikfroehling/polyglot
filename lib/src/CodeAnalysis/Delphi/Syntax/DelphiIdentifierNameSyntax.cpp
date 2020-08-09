#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiIdentifierNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiIdentifierNameSyntax::DelphiIdentifierNameSyntax(SyntaxKind syntaxKind,
                                                       std::shared_ptr<SyntaxToken> identifier) noexcept
    : DelphiSimpleNameSyntax{syntaxKind, std::move(identifier)}
{}

} // end namespace polyglot::CodeAnalysis
