#include "Delphi/Syntax/DelphiExceptionHandlerBlockSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiExceptionHandlerBlockSyntax::DelphiExceptionHandlerBlockSyntax(DelphiStatementListSyntax* exceptionHandlers,
                                                                     DelphiElseClauseSyntax* elseClause) noexcept
    : DelphiExceptionBlockSyntax{Core::Syntax::SyntaxKind::ExceptionHandlerBlock},
      _pExceptionHandlers{exceptionHandlers},
      _pElseClause{elseClause}
{}

DelphiExceptionHandlerBlockSyntax* DelphiExceptionHandlerBlockSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                             DelphiStatementListSyntax* exceptionHandlers,
                                                                             DelphiElseClauseSyntax* elseClause) noexcept
{
    assert(exceptionHandlers != nullptr);

    auto ptrExceptionHandlerBlockSyntax = std::make_unique<DelphiExceptionHandlerBlockSyntax>(exceptionHandlers, elseClause);
    return static_cast<DelphiExceptionHandlerBlockSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptionHandlerBlockSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
