#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiIdentifierNameSyntax : public DelphiSimpleNameSyntax
{
public:
    explicit DelphiIdentifierNameSyntax(Core::Syntax::ISyntaxToken* identifier) noexcept;
    virtual ~DelphiIdentifierNameSyntax() noexcept {}
    virtual Core::Syntax::ISyntaxToken* identifier() const noexcept override { return _pIdentifier; }
    inline pg_size childCount() const noexcept override final { return 1; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pIdentifier); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pIdentifier); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiIdentifierNameSyntax"; }

    static DelphiIdentifierNameSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* identifier) noexcept;

protected:
    Core::Syntax::ISyntaxToken* _pIdentifier;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H
