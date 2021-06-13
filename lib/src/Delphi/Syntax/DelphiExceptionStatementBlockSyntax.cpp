#include "Delphi/Syntax/DelphiExceptionStatementBlockSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiExceptionStatementBlockSyntax::DelphiExceptionStatementBlockSyntax(DelphiStatementListSyntax* statements) noexcept
    : DelphiExceptionBlockSyntax{SyntaxKind::ExceptionStatementBlock},
      _pStatements{statements}
{}

SyntaxVariant DelphiExceptionStatementBlockSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asList(_pStatements);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExceptionStatementBlockSyntax* DelphiExceptionStatementBlockSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                 DelphiStatementListSyntax* statements) noexcept
{
    assert(statements != nullptr);

    auto ptrExceptionStatementBlockSyntax = std::make_unique<DelphiExceptionStatementBlockSyntax>(statements);
    return static_cast<DelphiExceptionStatementBlockSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptionStatementBlockSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
