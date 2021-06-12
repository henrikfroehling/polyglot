#include "Delphi/Syntax/DelphiElseClauseSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiElseClauseSyntax::DelphiElseClauseSyntax(Core::Syntax::ISyntaxToken* elseKeyword,
                                               DelphiStatementSyntax* statement) noexcept
    : DelphiSyntaxNode{SyntaxKind::ElseClause},
      _pElseKeyword{elseKeyword},
      _pStatement{statement}
{}

DelphiElseClauseSyntax* DelphiElseClauseSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                       Core::Syntax::ISyntaxToken* elseKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
{
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseKeyword);
    assert(statement != nullptr);

    auto ptrElseClauseSyntax = std::make_unique<DelphiElseClauseSyntax>(elseKeyword, statement);
    return static_cast<DelphiElseClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrElseClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
