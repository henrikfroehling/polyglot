#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H

#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiProgramHeadSyntax : public DelphiSyntaxNode
{
public:
    DelphiProgramHeadSyntax() noexcept;
    virtual ~DelphiProgramHeadSyntax() noexcept {}
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
