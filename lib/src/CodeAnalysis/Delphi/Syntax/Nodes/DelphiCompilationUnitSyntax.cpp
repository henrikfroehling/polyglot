#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiCompilationUnitSyntax::DelphiCompilationUnitSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* EOFToken) noexcept
    : DelphiSyntaxNode{syntaxKind},
      _pEOFToken{EOFToken}
{
    adjustWidthAndFlags(_pEOFToken);
}

DelphiCompilationUnitSyntax* DelphiCompilationUnitSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 SyntaxKind syntaxKind,
                                                                 LanguageSyntaxToken* EOFToken) noexcept
{
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    auto ptrCompilationUnitSyntax = std::make_unique<DelphiCompilationUnitSyntax>(syntaxKind, EOFToken);
    return static_cast<DelphiCompilationUnitSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCompilationUnitSyntax)));
}

} // end namespace polyglot::CodeAnalysis
