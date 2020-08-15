#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiCompilationUnitSyntax::DelphiCompilationUnitSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiSyntaxNode{syntaxKind},
      _ptrEOFToken{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
