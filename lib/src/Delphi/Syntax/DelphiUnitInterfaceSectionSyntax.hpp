#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUsesClauseSyntax;

class DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(Core::Syntax::ISyntaxToken* interfaceKeyword,
                                              DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept {}
    inline Core::Syntax::ISyntaxToken* interfaceKeyword() const noexcept { return _pInterfaceKeyword; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline pg_size childCount() const noexcept override final { return _pUses != nullptr ? 2 : 1; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    static DelphiUnitInterfaceSectionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                    Core::Syntax::ISyntaxToken* interfaceKeyword,
                                                    DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pInterfaceKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
