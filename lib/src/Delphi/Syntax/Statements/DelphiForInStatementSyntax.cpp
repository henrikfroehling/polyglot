#include "Delphi/Syntax/Statements/DelphiForInStatementSyntax.hpp"
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

DelphiForInStatementSyntax::DelphiForInStatementSyntax(ISyntaxToken* forKeyword,
                                                       DelphiExpressionSyntax* elementExpression,
                                                       ISyntaxToken* inKeyword,
                                                       DelphiExpressionSyntax* collectionExpression,
                                                       ISyntaxToken* doKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
    : DelphiForStatementSyntax{SyntaxKind::ForInStatement, forKeyword, doKeyword, statement},
      _pElementExpression{elementExpression},
      _pInKeyword{inKeyword},
      _pCollectionExpression{collectionExpression}
{}

SyntaxVariant DelphiForInStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pForKeyword);
        case 1: return SyntaxVariant::asNode(_pElementExpression);
        case 2: return SyntaxVariant::asToken(_pInKeyword);
        case 3: return SyntaxVariant::asNode(_pCollectionExpression);
        case 4: return SyntaxVariant::asToken(_pDoKeyword);
        case 5: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiForInStatementSyntax* DelphiForInStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* forKeyword,
                                                               DelphiExpressionSyntax* elementExpression,
                                                               ISyntaxToken* inKeyword,
                                                               DelphiExpressionSyntax* collectionExpression,
                                                               ISyntaxToken* doKeyword,
                                                               DelphiStatementSyntax* statement) noexcept
{
    assert(forKeyword != nullptr);
    assert(forKeyword->syntaxKind() == SyntaxKind::ForKeyword);
    assert(elementExpression != nullptr);
    assert(inKeyword != nullptr);
    assert(inKeyword->syntaxKind() == SyntaxKind::InKeyword);
    assert(collectionExpression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrForInStatementSyntax = std::make_unique<DelphiForInStatementSyntax>(forKeyword, elementExpression, inKeyword,
                                                                                collectionExpression, doKeyword, statement);

    return static_cast<DelphiForInStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrForInStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
