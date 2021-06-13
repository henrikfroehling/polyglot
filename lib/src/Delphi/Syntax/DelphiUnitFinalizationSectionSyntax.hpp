#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitFinalizationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitFinalizationSectionSyntax() noexcept;
    virtual ~DelphiUnitFinalizationSectionSyntax() noexcept {}

    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiUnitFinalizationSectionSyntax"; }

    static DelphiUnitFinalizationSectionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
