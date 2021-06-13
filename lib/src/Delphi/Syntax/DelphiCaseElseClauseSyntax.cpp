#include "Delphi/Syntax/DelphiCaseElseClauseSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiCaseElseClauseSyntax::DelphiCaseElseClauseSyntax(Core::Syntax::ISyntaxToken* elseKeyword,
                                                       DelphiStatementListSyntax* statements) noexcept
    : DelphiSyntaxNode{SyntaxKind::CaseElseClause},
      _pElseKeyword{elseKeyword},
      _pStatements{statements}
{}

DelphiCaseElseClauseSyntax* DelphiCaseElseClauseSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* elseKeyword,
                                                               DelphiStatementListSyntax* statements) noexcept
{
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseKeyword);
    assert(statements != nullptr);

    auto ptrCaseElseClauseSyntax = std::make_unique<DelphiCaseElseClauseSyntax>(elseKeyword, statements);
    return static_cast<DelphiCaseElseClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCaseElseClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
