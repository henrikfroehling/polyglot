#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H

#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiPackageContainsClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageContainsClauseSyntax() noexcept;
    virtual ~DelphiPackageContainsClauseSyntax() noexcept {}
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
