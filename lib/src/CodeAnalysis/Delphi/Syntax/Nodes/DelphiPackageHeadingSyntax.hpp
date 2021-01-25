#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEHEADINGSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiPackageHeadingSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageHeadingSyntax() noexcept;
    virtual ~DelphiPackageHeadingSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEHEADINGSYNTAX_H
