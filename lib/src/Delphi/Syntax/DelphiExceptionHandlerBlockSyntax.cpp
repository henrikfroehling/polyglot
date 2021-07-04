#include "Delphi/Syntax/DelphiExceptionHandlerBlockSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiExceptionHandlerBlockSyntax::DelphiExceptionHandlerBlockSyntax(DelphiStatementListSyntax* exceptionHandlers,
                                                                     DelphiTryElseClauseSyntax* elseClause) noexcept
    : DelphiExceptionBlockSyntax{SyntaxKind::ExceptionHandlerBlock},
      _pExceptionHandlers{exceptionHandlers},
      _pElseClause{elseClause}
{
    _position = _pExceptionHandlers->position();
    adjustWidthAndFlags(_pExceptionHandlers);
    adjustWidthAndFlags(_pElseClause);
}

SyntaxVariant DelphiExceptionHandlerBlockSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 1:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asList(_pExceptionHandlers);
            }
        }
        case 2:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asList(_pExceptionHandlers);
                case 1: return SyntaxVariant::asNode(_pElseClause);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExceptionHandlerBlockSyntax* DelphiExceptionHandlerBlockSyntax::create(SyntaxFactory& syntaxFactory,
                                                                             DelphiStatementListSyntax* exceptionHandlers,
                                                                             DelphiTryElseClauseSyntax* elseClause) noexcept
{
    assert(exceptionHandlers != nullptr);

    auto ptrExceptionHandlerBlockSyntax = std::make_unique<DelphiExceptionHandlerBlockSyntax>(exceptionHandlers, elseClause);
    return static_cast<DelphiExceptionHandlerBlockSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptionHandlerBlockSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
