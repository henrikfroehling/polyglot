#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISTATEMENTLISTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISTATEMENTLISTSYNTAX_H

#include <vector>
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxList.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiStatementListSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiStatementListSyntax(std::vector<Core::Syntax::SyntaxVariant>&& statements) noexcept;
    virtual ~DelphiStatementListSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiStatementListSyntax"; }

    static DelphiStatementListSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             std::vector<Core::Syntax::SyntaxVariant>&& statements) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISTATEMENTLISTSYNTAX_H
