#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax;

namespace polyglot::Delphi::Syntax
{

class DelphiPackageContainsClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageContainsClauseSyntax() noexcept;
    virtual ~DelphiPackageContainsClauseSyntax() noexcept {}

    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::empty(); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiPackageContainsClauseSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
