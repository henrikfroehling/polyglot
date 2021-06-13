#include "Delphi/Syntax/DelphiExceptClauseSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiExceptClauseSyntax::DelphiExceptClauseSyntax(Core::Syntax::ISyntaxToken* exceptKeyword,
                                                   DelphiExceptionBlockSyntax* exceptionBlock) noexcept
    : DelphiSyntaxNode{SyntaxKind::ExceptClause},
      _pExceptKeyword{exceptKeyword},
      _pExceptionBlock{exceptionBlock}
{}

DelphiExceptClauseSyntax* DelphiExceptClauseSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                           Core::Syntax::ISyntaxToken* exceptKeyword,
                                                           DelphiExceptionBlockSyntax* exceptionBlock) noexcept
{
    assert(exceptKeyword != nullptr);
    assert(exceptKeyword->syntaxKind() == SyntaxKind::ExceptKeyword);
    assert(exceptionBlock != nullptr);

    auto ptrExceptClauseSyntax = std::make_unique<DelphiExceptClauseSyntax>(exceptKeyword, exceptionBlock);
    return static_cast<DelphiExceptClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
