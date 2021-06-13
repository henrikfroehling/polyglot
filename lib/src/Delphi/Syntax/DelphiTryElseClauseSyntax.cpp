#include "Delphi/Syntax/DelphiTryElseClauseSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiTryElseClauseSyntax::DelphiTryElseClauseSyntax(Core::Syntax::ISyntaxToken* elseKeyword,
                                                     DelphiStatementListSyntax* statements) noexcept
    : DelphiSyntaxNode{SyntaxKind::TryElseClause},
      _pElseKeyword{elseKeyword},
      _pStatements{statements}
{}

DelphiTryElseClauseSyntax* DelphiTryElseClauseSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* elseKeyword,
                                                             DelphiStatementListSyntax* statements) noexcept
{
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseKeyword);
    assert(statements != nullptr);

    auto ptrTryElseClauseSyntax = std::make_unique<DelphiTryElseClauseSyntax>(elseKeyword, statements);
    return static_cast<DelphiTryElseClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrTryElseClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
