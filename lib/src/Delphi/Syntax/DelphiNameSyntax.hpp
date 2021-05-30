#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHINAMESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHINAMESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiTypeSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiNameSyntax : public DelphiTypeSyntax
{
public:
    explicit DelphiNameSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiNameSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiNameSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHINAMESYNTAX_H
