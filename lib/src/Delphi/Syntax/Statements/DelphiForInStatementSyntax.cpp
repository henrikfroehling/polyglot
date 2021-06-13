#include "Delphi/Syntax/Statements/DelphiForInStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiForInStatementSyntax::DelphiForInStatementSyntax(Core::Syntax::ISyntaxToken* forKeyword,
                                                       DelphiExpressionSyntax* elementExpression,
                                                       Core::Syntax::ISyntaxToken* inKeyword,
                                                       DelphiExpressionSyntax* collectionExpression,
                                                       Core::Syntax::ISyntaxToken* doKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
    : DelphiForStatementSyntax{SyntaxKind::ForInStatement, forKeyword, doKeyword, statement},
      _pElementExpression{elementExpression},
      _pInKeyword{inKeyword},
      _pCollectionExpression{collectionExpression}
{}

DelphiForInStatementSyntax* DelphiForInStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* forKeyword,
                                                               DelphiExpressionSyntax* elementExpression,
                                                               Core::Syntax::ISyntaxToken* inKeyword,
                                                               DelphiExpressionSyntax* collectionExpression,
                                                               Core::Syntax::ISyntaxToken* doKeyword,
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
