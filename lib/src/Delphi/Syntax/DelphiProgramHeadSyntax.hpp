#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H

#include "polyglot/Core/Types.hpp"
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

    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiProgramHeadSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMHEADSYNTAX_H
