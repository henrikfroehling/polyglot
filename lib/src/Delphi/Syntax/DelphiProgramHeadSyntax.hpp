#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H

#include <string>
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

    virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }
    virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }

    virtual std::string typeName() const noexcept override { return "DelphiProgramHeadSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
