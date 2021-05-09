#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitFinalizationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitFinalizationSectionSyntax() noexcept;
    virtual ~DelphiUnitFinalizationSectionSyntax() noexcept {}

    static DelphiUnitFinalizationSectionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
