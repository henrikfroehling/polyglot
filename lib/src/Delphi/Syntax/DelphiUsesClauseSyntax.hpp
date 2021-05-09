#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
#include "polyglot/Core/Types.hpp"
#include "DelphiSyntaxList.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxList;
class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUsesClauseSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiUsesClauseSyntax(Core::Syntax::ISyntaxToken* usesKeyword,
                                    Core::Syntax::ISyntaxList* unitReferences,
                                    Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* usesKeyword() const noexcept { return _pUsesKeyword; }
    inline Core::Syntax::ISyntaxList* unitReferences() const noexcept { return _pUnitReferences; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline pg_size childCount() const noexcept override final { return 3; }
    inline Core::Syntax::SyntaxNodeOrToken child(pg_size index) const override final;

    inline Core::Syntax::SyntaxNodeOrToken first() const noexcept override final { return Core::Syntax::SyntaxNodeOrToken::asToken(_pUsesKeyword); }
    inline Core::Syntax::SyntaxNodeOrToken last() const noexcept override final { return Core::Syntax::SyntaxNodeOrToken::asToken(_pSemiColonToken); }

    static DelphiUsesClauseSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                          Core::Syntax::ISyntaxToken* usesKeyword,
                                          Core::Syntax::ISyntaxList* unitReferences,
                                          Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pUsesKeyword;
    Core::Syntax::ISyntaxList* _pUnitReferences;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
