#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiNameSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSimpleNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiSimpleNameSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSimpleNameSyntax() noexcept {}
    virtual Core::Syntax::ISyntaxToken* identifier() const noexcept = 0;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSimpleNameSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
