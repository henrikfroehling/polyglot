#include "Delphi/Syntax/Statements/DelphiContinueStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiContinueStatementSyntax::DelphiContinueStatementSyntax(Core::Syntax::ISyntaxToken* continueKeyword,
                                                             Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::ContinueStatement},
      _pContinueKeyword{continueKeyword},
      _pSemiColonToken{semiColonToken}
{}

DelphiContinueStatementSyntax* DelphiContinueStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                     Core::Syntax::ISyntaxToken* continueKeyword,
                                                                     Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(continueKeyword != nullptr);
    assert(continueKeyword->syntaxKind() == SyntaxKind::ContinueKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrContinueStatementSyntax = std::make_unique<DelphiContinueStatementSyntax>(continueKeyword, semiColonToken);
    return static_cast<DelphiContinueStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrContinueStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
