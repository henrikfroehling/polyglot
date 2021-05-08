#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class SyntaxFactory;

class DelphiUnitFinalizationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitFinalizationSectionSyntax() noexcept;
    virtual ~DelphiUnitFinalizationSectionSyntax() noexcept = default;

    static DelphiUnitFinalizationSectionSyntax* create(SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
