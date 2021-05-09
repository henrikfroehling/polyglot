#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiPackageRequiresClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageRequiresClauseSyntax() noexcept;
    virtual ~DelphiPackageRequiresClauseSyntax() noexcept {}
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H
