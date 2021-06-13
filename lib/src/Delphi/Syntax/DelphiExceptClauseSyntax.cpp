#include "Delphi/Syntax/DelphiExceptClauseSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiExceptClauseSyntax::DelphiExceptClauseSyntax(ISyntaxToken* exceptKeyword,
                                                   DelphiExceptionBlockSyntax* exceptionBlock) noexcept
    : DelphiSyntaxNode{SyntaxKind::ExceptClause},
      _pExceptKeyword{exceptKeyword},
      _pExceptionBlock{exceptionBlock}
{}

SyntaxVariant DelphiExceptClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pExceptKeyword);
        case 1: return SyntaxVariant::asNode(_pExceptionBlock);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExceptClauseSyntax* DelphiExceptClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                           ISyntaxToken* exceptKeyword,
                                                           DelphiExceptionBlockSyntax* exceptionBlock) noexcept
{
    assert(exceptKeyword != nullptr);
    assert(exceptKeyword->syntaxKind() == SyntaxKind::ExceptKeyword);
    assert(exceptionBlock != nullptr);

    auto ptrExceptClauseSyntax = std::make_unique<DelphiExceptClauseSyntax>(exceptKeyword, exceptionBlock);
    return static_cast<DelphiExceptClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
