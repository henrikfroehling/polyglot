#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPROGRAMMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiProgramHeadingSyntax;
class DelphiUsesClauseSyntax;
class SyntaxFactory;

class DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiProgramModuleSyntax(DelphiProgramHeadingSyntax* heading,
                                       DelphiUsesClauseSyntax* uses,
                                       LanguageSyntaxToken* EOFToken) noexcept;

    virtual ~DelphiProgramModuleSyntax() noexcept = default;
    inline bool isProgramModule() const noexcept override { return true; }
    inline DelphiProgramHeadingSyntax* heading() const noexcept { return _pHeading; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }

    static DelphiProgramModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                             DelphiProgramHeadingSyntax* heading,
                                             DelphiUsesClauseSyntax* uses,
                                             LanguageSyntaxToken* EOFToken) noexcept;

    static DelphiProgramModuleSyntax* create(SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiProgramHeadingSyntax* _pHeading;
    DelphiUsesClauseSyntax* _pUses;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPROGRAMMODULESYNTAX_H
