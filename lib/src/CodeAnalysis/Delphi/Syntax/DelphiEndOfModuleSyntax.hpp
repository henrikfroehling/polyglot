#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiEndOfModuleSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiEndOfModuleSyntax(LanguageSyntaxToken* endKeyword,
                                     LanguageSyntaxToken* dotToken) noexcept;

    virtual ~DelphiEndOfModuleSyntax() noexcept = default;

    inline LanguageSyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline LanguageSyntaxToken* dotToken() const noexcept { return _pDotToken; }

    static DelphiEndOfModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                           LanguageSyntaxToken* endKeyword,
                                           LanguageSyntaxToken* dotToken) noexcept;

private:
    LanguageSyntaxToken* _pEndKeyword;
    LanguageSyntaxToken* _pDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H
