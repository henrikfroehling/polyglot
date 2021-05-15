#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(Core::Syntax::ISyntaxToken* implementationKeyword,
                                                   DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitImplementationSectionSyntax() noexcept {}
    inline Core::Syntax::ISyntaxToken* implementationKeyword() const noexcept { return _pImplementationKeyword; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline pg_size childCount() const noexcept override final { return _pUses != nullptr ? 2 : 1; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::ISyntaxToken* firstToken() const noexcept override final { return _pImplementationKeyword; }
    inline Core::Syntax::ISyntaxToken* lastToken() const noexcept override final { return _pUses != nullptr ? _pUses->last().token : _pImplementationKeyword; }

    static DelphiUnitImplementationSectionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                         Core::Syntax::ISyntaxToken* implementationKeyword,
                                                         DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pImplementationKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // #ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
