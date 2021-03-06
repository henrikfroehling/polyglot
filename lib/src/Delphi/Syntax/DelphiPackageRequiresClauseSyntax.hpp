#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax;

namespace polyglot::Delphi::Syntax
{

class DelphiPackageRequiresClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageRequiresClauseSyntax() noexcept;
    virtual ~DelphiPackageRequiresClauseSyntax() noexcept {}

    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiPackageRequiresClauseSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H
