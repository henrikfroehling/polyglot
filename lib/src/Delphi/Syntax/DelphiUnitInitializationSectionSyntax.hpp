#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class SyntaxFactory;

class DelphiUnitInitializationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitInitializationSectionSyntax() noexcept;
    virtual ~DelphiUnitInitializationSectionSyntax() noexcept = default;

    static DelphiUnitInitializationSectionSyntax* create(SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
