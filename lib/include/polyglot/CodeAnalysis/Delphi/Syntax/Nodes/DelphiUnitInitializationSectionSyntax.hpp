#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitInitializationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitInitializationSectionSyntax() noexcept;
    virtual ~DelphiUnitInitializationSectionSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
