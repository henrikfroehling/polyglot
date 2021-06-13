#include "Delphi/Syntax/DelphiCaseElseClauseSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiCaseElseClauseSyntax::DelphiCaseElseClauseSyntax(ISyntaxToken* elseKeyword,
                                                       DelphiStatementListSyntax* statements) noexcept
    : DelphiSyntaxNode{SyntaxKind::CaseElseClause},
      _pElseKeyword{elseKeyword},
      _pStatements{statements}
{}

SyntaxVariant DelphiCaseElseClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pElseKeyword);
        case 1: return SyntaxVariant::asList(_pStatements);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiCaseElseClauseSyntax* DelphiCaseElseClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* elseKeyword,
                                                               DelphiStatementListSyntax* statements) noexcept
{
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseKeyword);
    assert(statements != nullptr);

    auto ptrCaseElseClauseSyntax = std::make_unique<DelphiCaseElseClauseSyntax>(elseKeyword, statements);
    return static_cast<DelphiCaseElseClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCaseElseClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
