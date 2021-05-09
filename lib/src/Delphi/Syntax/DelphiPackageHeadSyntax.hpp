#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEHEADSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiPackageHeadSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageHeadSyntax() noexcept;
    virtual ~DelphiPackageHeadSyntax() noexcept {}
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEHEADSYNTAX_H
