#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "Delphi/Syntax/DelphiPackageHeadSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiPackageContainsClauseSyntax;
class DelphiPackageRequiresClauseSyntax;

class DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiPackageModuleSyntax(DelphiPackageHeadSyntax* head,
                                       DelphiPackageRequiresClauseSyntax* requiresClause,
                                       DelphiPackageContainsClauseSyntax* containsClause,
                                       Core::Syntax::ISyntaxToken* EOFToken) noexcept;

    virtual ~DelphiPackageModuleSyntax() noexcept {}
    inline bool isPackageModule() const noexcept override { return true; }
    inline DelphiPackageHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _pRequiresClause; }
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _pContainsClause; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::ISyntaxToken* firstToken() const noexcept override final { return _pHead->firstToken(); }
    inline Core::Syntax::ISyntaxToken* lastToken() const noexcept override final { return _pEOFToken; }

    static DelphiPackageModuleSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             DelphiPackageHeadSyntax* head,
                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                             DelphiPackageContainsClauseSyntax* containsClause,
                                             Core::Syntax::ISyntaxToken* EOFToken) noexcept;

    static DelphiPackageModuleSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiPackageHeadSyntax* _pHead;
    DelphiPackageRequiresClauseSyntax* _pRequiresClause;
    DelphiPackageContainsClauseSyntax* _pContainsClause;
};

} // polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
