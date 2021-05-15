#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H

#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax;

namespace polyglot::Delphi::Syntax
{

class DelphiProgramHeadSyntax : public DelphiSyntaxNode
{
public:
    DelphiProgramHeadSyntax() noexcept;
    virtual ~DelphiProgramHeadSyntax() noexcept {}

    virtual Core::Syntax::ISyntaxToken* firstToken() const noexcept override { return nullptr; }
    virtual Core::Syntax::ISyntaxToken* lastToken() const noexcept override { return nullptr; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
