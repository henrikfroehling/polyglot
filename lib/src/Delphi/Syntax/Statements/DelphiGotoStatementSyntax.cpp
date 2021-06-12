#include "Delphi/Syntax/Statements/DelphiGotoStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiGotoStatementSyntax::DelphiGotoStatementSyntax(Core::Syntax::ISyntaxToken* gotoKeyword,
                                                     Core::Syntax::ISyntaxToken* labelToken,
                                                     Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::GotoStatement},
      _pGotoKeyword{gotoKeyword},
      _pLabelToken{labelToken},
      _pSemiColonToken{semiColonToken}
{}

DelphiGotoStatementSyntax* DelphiGotoStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* gotoKeyword,
                                                             Core::Syntax::ISyntaxToken* labelToken,
                                                             Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(gotoKeyword != nullptr);
    assert(gotoKeyword->syntaxKind() == SyntaxKind::GotoKeyword);
    assert(labelToken != nullptr);
    const SyntaxKind labelSyntaxKind = labelToken->syntaxKind();
    assert(labelSyntaxKind == SyntaxKind::IdentifierToken || labelSyntaxKind == SyntaxKind::IntegerNumberLiteralToken);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrGotoStatementSyntax = std::make_unique<DelphiGotoStatementSyntax>(gotoKeyword, labelToken, semiColonToken);
    return static_cast<DelphiGotoStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrGotoStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
