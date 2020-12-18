#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitFinalizationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitFinalizationSectionSyntax() noexcept;
    virtual ~DelphiUnitFinalizationSectionSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
