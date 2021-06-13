#include "Delphi/Syntax/Statements/DelphiContinueStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiContinueStatementSyntax::DelphiContinueStatementSyntax(ISyntaxToken* continueKeyword,
                                                             ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::ContinueStatement},
      _pContinueKeyword{continueKeyword},
      _pSemiColonToken{semiColonToken}
{}

SyntaxVariant DelphiContinueStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pContinueKeyword);
        case 1: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiContinueStatementSyntax* DelphiContinueStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                     ISyntaxToken* continueKeyword,
                                                                     ISyntaxToken* semiColonToken) noexcept
{
    assert(continueKeyword != nullptr);
    assert(continueKeyword->syntaxKind() == SyntaxKind::ContinueKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrContinueStatementSyntax = std::make_unique<DelphiContinueStatementSyntax>(continueKeyword, semiColonToken);
    return static_cast<DelphiContinueStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrContinueStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
