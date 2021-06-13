#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICASEITEMLISTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICASEITEMLISTSYNTAX_H

#include <vector>
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxList.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCaseItemListSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiCaseItemListSyntax(std::vector<Core::Syntax::SyntaxVariant>&& caseItems) noexcept;
    virtual ~DelphiCaseItemListSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseItemListSyntax"; }

    static DelphiCaseItemListSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                            std::vector<Core::Syntax::SyntaxVariant>&& caseItems) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICASEITEMLISTSYNTAX_H
