#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiPackageContainsClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageContainsClauseSyntax() noexcept;
    virtual ~DelphiPackageContainsClauseSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
