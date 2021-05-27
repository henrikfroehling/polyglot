#include "Delphi/Syntax/DelphiContinueStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiContinueStatementSyntax::DelphiContinueStatementSyntax(Core::Syntax::ISyntaxToken* continueKeyword) noexcept
    : DelphiSimpleStatementSyntax{SyntaxKind::ContinueStatement},
      _pContinueKeyword{continueKeyword}
{}

DelphiContinueStatementSyntax* DelphiContinueStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                     Core::Syntax::ISyntaxToken* continueKeyword) noexcept
{
    assert(continueKeyword != nullptr);
    assert(continueKeyword->syntaxKind() == SyntaxKind::ContinueKeyword);

    auto ptrContinueStatementSyntax = std::make_unique<DelphiContinueStatementSyntax>(continueKeyword);
    return static_cast<DelphiContinueStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrContinueStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
