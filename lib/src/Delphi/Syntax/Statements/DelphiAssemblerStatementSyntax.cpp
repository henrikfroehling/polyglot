#include "Delphi/Syntax/Statements/DelphiAssemblerStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiAssemblerStatementSyntax::DelphiAssemblerStatementSyntax(Core::Syntax::ISyntaxToken* asmKeyword,
                                                               Core::Syntax::ISyntaxToken* endKeyword,
                                                               Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::AssemblerStatement},
      _pAsmKeyword{asmKeyword},
      _pEndKeyword{endKeyword},
      _pSemiColonToken{semiColonToken}
{}

DelphiAssemblerStatementSyntax* DelphiAssemblerStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                       Core::Syntax::ISyntaxToken* asmKeyword,
                                                                       Core::Syntax::ISyntaxToken* endKeyword,
                                                                       Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(asmKeyword != nullptr);
    assert(asmKeyword->syntaxKind() == SyntaxKind::AsmKeyword);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrAssemblerStatementSyntax = std::make_unique<DelphiAssemblerStatementSyntax>(asmKeyword, endKeyword, semiColonToken);
    return static_cast<DelphiAssemblerStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrAssemblerStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
