#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

DelphiCompilationUnitSyntax::DelphiCompilationUnitSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiSyntaxNode{syntaxKind},
      _pEOFToken{nullptr}
{
    adjustWidthAndFlags(_pEOFToken);
}

} // end namespace polyglot::CodeAnalysis
