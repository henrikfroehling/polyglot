#include "Delphi/Syntax/DelphiFinallyClauseSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiFinallyClauseSyntax::DelphiFinallyClauseSyntax(Core::Syntax::ISyntaxToken* finallyKeyword,
                                                     DelphiStatementListSyntax* statements) noexcept
    : DelphiSyntaxNode{SyntaxKind::FinallyClause},
      _pFinallyKeyword{finallyKeyword},
      _pStatements{statements}
{}

DelphiFinallyClauseSyntax* DelphiFinallyClauseSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* finallyKeyword,
                                                             DelphiStatementListSyntax* statements) noexcept
{
    assert(finallyKeyword != nullptr);
    assert(finallyKeyword->syntaxKind() == SyntaxKind::FinallyKeyword);
    assert(statements != nullptr);

    auto ptrFinallyClauseSyntax = std::make_unique<DelphiFinallyClauseSyntax>(finallyKeyword, statements);
    return static_cast<DelphiFinallyClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrFinallyClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
