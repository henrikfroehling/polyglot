#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiStatementListSyntax::DelphiStatementListSyntax(std::vector<Core::Syntax::SyntaxVariant>&& statements) noexcept
    : DelphiSyntaxList{Core::Syntax::SyntaxKind::StatementList, std::move(statements)}
{}

DelphiStatementListSyntax* DelphiStatementListSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             std::vector<Core::Syntax::SyntaxVariant>&& statements) noexcept
{

    auto ptrStatementListSyntax = std::make_unique<DelphiStatementListSyntax>(std::move(statements));
    return static_cast<DelphiStatementListSyntax*>(syntaxFactory.addSyntaxList(std::move(ptrStatementListSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
