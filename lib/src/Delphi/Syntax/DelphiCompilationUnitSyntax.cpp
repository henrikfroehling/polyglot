#include "Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;

DelphiCompilationUnitSyntax::DelphiCompilationUnitSyntax(SyntaxKind syntaxKind,
                                                         ISyntaxToken* EOFToken) noexcept
    : DelphiSyntaxNode{syntaxKind},
      _pEOFToken{EOFToken}
{}

DelphiCompilationUnitSyntax* DelphiCompilationUnitSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 SyntaxKind syntaxKind,
                                                                 ISyntaxToken* EOFToken) noexcept
{
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    auto ptrCompilationUnitSyntax = std::make_unique<DelphiCompilationUnitSyntax>(syntaxKind, EOFToken);
    return dynamic_cast<DelphiCompilationUnitSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCompilationUnitSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
