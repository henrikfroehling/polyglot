#include "Delphi/Syntax/DelphiBreakStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiBreakStatementSyntax::DelphiBreakStatementSyntax(Core::Syntax::ISyntaxToken* breakKeyword) noexcept
    : DelphiSimpleStatementSyntax{SyntaxKind::BreakStatement},
      _pBreakKeyword{breakKeyword}
{}

DelphiBreakStatementSyntax* DelphiBreakStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* breakKeyword) noexcept
{
    assert(breakKeyword != nullptr);
    assert(breakKeyword->syntaxKind() == SyntaxKind::BreakKeyword);

    auto ptrBreakStatementSyntax = std::make_unique<DelphiBreakStatementSyntax>(breakKeyword);
    return static_cast<DelphiBreakStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBreakStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
