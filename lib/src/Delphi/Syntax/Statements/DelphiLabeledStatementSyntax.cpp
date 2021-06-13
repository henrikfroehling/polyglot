#include "Delphi/Syntax/Statements/DelphiLabeledStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiLabeledStatementSyntax::DelphiLabeledStatementSyntax(ISyntaxToken* labelIdentifier,
                                                           ISyntaxToken* colonToken,
                                                           DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{SyntaxKind::LabeledStatement},
      _pLabelIdentifier{labelIdentifier},
      _pColonToken{colonToken},
      _pStatement{statement}
{}

SyntaxVariant DelphiLabeledStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pLabelIdentifier);
        case 1: return SyntaxVariant::asToken(_pColonToken);
        case 2: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiLabeledStatementSyntax* DelphiLabeledStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                   ISyntaxToken* labelIdentifier,
                                                                   ISyntaxToken* colonToken,
                                                                   DelphiStatementSyntax* statement) noexcept
{
    assert(labelIdentifier != nullptr);
    assert(labelIdentifier->syntaxKind() == SyntaxKind::IdentifierToken || labelIdentifier->syntaxKind() == SyntaxKind::IntegerNumberLiteralToken);
    assert(colonToken != nullptr);
    assert(colonToken->syntaxKind() == SyntaxKind::ColonToken);

    auto ptrLabeledStatementSyntax = std::make_unique<DelphiLabeledStatementSyntax>(labelIdentifier, colonToken, statement);
    return static_cast<DelphiLabeledStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrLabeledStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
