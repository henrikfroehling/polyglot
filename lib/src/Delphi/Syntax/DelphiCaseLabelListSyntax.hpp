#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICASELABELLISTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICASELABELLISTSYNTAX_H

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

class DelphiCaseLabelListSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiCaseLabelListSyntax(std::vector<Core::Syntax::SyntaxVariant>&& labels) noexcept;
    virtual ~DelphiCaseLabelListSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseLabelListSyntax"; }

    static DelphiCaseLabelListSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             std::vector<Core::Syntax::SyntaxVariant>&& labels) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICASELABELLISTSYNTAX_H
