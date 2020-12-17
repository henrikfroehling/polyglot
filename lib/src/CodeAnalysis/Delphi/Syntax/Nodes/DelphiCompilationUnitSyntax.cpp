#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiCompilationUnitSyntax::DelphiCompilationUnitSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiSyntaxNode{syntaxKind},
      _pEOFToken{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
