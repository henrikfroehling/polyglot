#include "Delphi/Syntax/DelphiExceptionStatementBlockSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiExceptionStatementBlockSyntax::DelphiExceptionStatementBlockSyntax(DelphiStatementListSyntax* statements) noexcept
    : DelphiExceptionBlockSyntax{Core::Syntax::SyntaxKind::ExceptionStatementBlock},
      _pStatements{statements}
{}

DelphiExceptionStatementBlockSyntax* DelphiExceptionStatementBlockSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                                 DelphiStatementListSyntax* statements) noexcept
{
    assert(statements != nullptr);

    auto ptrExceptionStatementBlockSyntax = std::make_unique<DelphiExceptionStatementBlockSyntax>(statements);
    return static_cast<DelphiExceptionStatementBlockSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptionStatementBlockSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
