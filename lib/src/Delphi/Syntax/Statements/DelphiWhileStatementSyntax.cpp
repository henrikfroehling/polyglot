#include "Delphi/Syntax/Statements/DelphiWhileStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiWhileStatementSyntax::DelphiWhileStatementSyntax(ISyntaxToken* whileKeyword,
                                                       DelphiExpressionSyntax* expression,
                                                       ISyntaxToken* doKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{SyntaxKind::WhileStatement},
      _pWhileKeyword{whileKeyword},
      _pExpression{expression},
      _pDoKeyword{doKeyword},
      _pStatement{statement}
{}

SyntaxVariant DelphiWhileStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pWhileKeyword);
        case 1: return SyntaxVariant::asNode(_pExpression);
        case 2: return SyntaxVariant::asToken(_pDoKeyword);
        case 3: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiWhileStatementSyntax* DelphiWhileStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* whileKeyword,
                                                               DelphiExpressionSyntax* expression,
                                                               ISyntaxToken* doKeyword,
                                                               DelphiStatementSyntax* statement) noexcept
{
    assert(whileKeyword != nullptr);
    assert(whileKeyword->syntaxKind() == SyntaxKind::WhileKeyword);
    assert(expression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrWhileStatementSyntax = std::make_unique<DelphiWhileStatementSyntax>(whileKeyword, expression, doKeyword, statement);
    return static_cast<DelphiWhileStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrWhileStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
