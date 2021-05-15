#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H

#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitFinalizationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitFinalizationSectionSyntax() noexcept;
    virtual ~DelphiUnitFinalizationSectionSyntax() noexcept {}

    virtual Core::Syntax::ISyntaxToken* firstToken() const noexcept override { return nullptr; }
    virtual Core::Syntax::ISyntaxToken* lastToken() const noexcept override { return nullptr; }

    static DelphiUnitFinalizationSectionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
