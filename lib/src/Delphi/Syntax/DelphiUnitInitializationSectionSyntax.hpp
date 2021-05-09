#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitInitializationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitInitializationSectionSyntax() noexcept;
    virtual ~DelphiUnitInitializationSectionSyntax() noexcept {}

    static DelphiUnitInitializationSectionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINITIALIZATIONSECTIONSYNTAX_H
