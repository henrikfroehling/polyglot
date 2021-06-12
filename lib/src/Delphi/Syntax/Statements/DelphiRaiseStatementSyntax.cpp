#include "Delphi/Syntax/Statements/DelphiRaiseStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiRaiseStatementSyntax::DelphiRaiseStatementSyntax(Core::Syntax::ISyntaxToken* raiseKeyword,
                                                       Core::Syntax::ISyntaxToken* semiColonToken,
                                                       DelphiExpressionSyntax* expression) noexcept
    : DelphiStatementSyntax{SyntaxKind::RaiseStatement},
      _pRaiseKeyword{raiseKeyword},
      _pSemiColonToken{semiColonToken},
      _pExpression{expression}
{}

DelphiRaiseStatementSyntax* DelphiRaiseStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* raiseKeyword,
                                                               Core::Syntax::ISyntaxToken* semiColonToken,
                                                               DelphiExpressionSyntax* expression) noexcept
{
    assert(raiseKeyword != nullptr);
    assert(raiseKeyword->syntaxKind() == SyntaxKind::RaiseKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrRaiseStatementSyntax = std::make_unique<DelphiRaiseStatementSyntax>(raiseKeyword, semiColonToken, expression);
    return static_cast<DelphiRaiseStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrRaiseStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
