#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "Delphi/Syntax/DelphiProgramHeadSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUsesClauseSyntax;

class DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiProgramModuleSyntax(DelphiProgramHeadSyntax* head,
                                       DelphiUsesClauseSyntax* uses,
                                       Core::Syntax::ISyntaxToken* EOFToken) noexcept;

    virtual ~DelphiProgramModuleSyntax() noexcept {}
    inline bool isProgramModule() const noexcept override { return true; }
    inline DelphiProgramHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::ISyntaxToken* firstToken() const noexcept override final { return _pHead->firstToken(); }
    inline Core::Syntax::ISyntaxToken* lastToken() const noexcept override final { return _pEOFToken; }

    static DelphiProgramModuleSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             DelphiProgramHeadSyntax* head,
                                             DelphiUsesClauseSyntax* uses,
                                             Core::Syntax::ISyntaxToken* EOFToken) noexcept;

    static DelphiProgramModuleSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiProgramHeadSyntax* _pHead;
    DelphiUsesClauseSyntax* _pUses;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
