#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxFactory;

class DelphiUnitInitializationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitInitializationSectionSyntax() noexcept;
    virtual ~DelphiUnitInitializationSectionSyntax() noexcept = default;

    static DelphiUnitInitializationSectionSyntax* create(SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
