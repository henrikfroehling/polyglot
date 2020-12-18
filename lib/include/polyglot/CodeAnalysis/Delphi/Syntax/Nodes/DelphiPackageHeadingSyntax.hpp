#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEHEADINGSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiPackageHeadingSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageHeadingSyntax() noexcept;
    virtual ~DelphiPackageHeadingSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEHEADINGSYNTAX_H
