#include "Delphi/Syntax/Statements/DelphiBreakStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiBreakStatementSyntax::DelphiBreakStatementSyntax(Core::Syntax::ISyntaxToken* breakKeyword,
                                                       Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::BreakStatement},
      _pBreakKeyword{breakKeyword},
      _pSemiColonToken{semiColonToken}
{}

DelphiBreakStatementSyntax* DelphiBreakStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* breakKeyword,
                                                               Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(breakKeyword != nullptr);
    assert(breakKeyword->syntaxKind() == SyntaxKind::BreakKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrBreakStatementSyntax = std::make_unique<DelphiBreakStatementSyntax>(breakKeyword, semiColonToken);
    return static_cast<DelphiBreakStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBreakStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
