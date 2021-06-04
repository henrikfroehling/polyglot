#include "Delphi/Syntax/Statements/DelphiLabeledStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiLabeledStatementSyntax::DelphiLabeledStatementSyntax(Core::Syntax::ISyntaxToken* labelIdentifier,
                                                           Core::Syntax::ISyntaxToken* colonToken,
                                                           DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{SyntaxKind::LabeledStatement},
      _pLabelIdentifier{labelIdentifier},
      _pColonToken{colonToken},
      _pStatement{statement}
{}

DelphiLabeledStatementSyntax* DelphiLabeledStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                   Core::Syntax::ISyntaxToken* labelIdentifier,
                                                                   Core::Syntax::ISyntaxToken* colonToken,
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
