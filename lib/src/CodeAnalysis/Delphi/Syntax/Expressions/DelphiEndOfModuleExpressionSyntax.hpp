#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_EXPRESSIONS_DELPHIENDOFMODULEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_EXPRESSIONS_DELPHIENDOFMODULEEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiEndOfModuleExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiEndOfModuleExpressionSyntax(LanguageSyntaxToken* endKeyword,
                                               LanguageSyntaxToken* dotToken) noexcept;

    virtual ~DelphiEndOfModuleExpressionSyntax() noexcept = default;

    inline LanguageSyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline LanguageSyntaxToken* dotToken() const noexcept { return _pDotToken; }

    static DelphiEndOfModuleExpressionSyntax* create(SyntaxFactory& syntaxFactory,
                                                     LanguageSyntaxToken* endKeyword,
                                                     LanguageSyntaxToken* dotToken) noexcept;

private:
    LanguageSyntaxToken* _pEndKeyword;
    LanguageSyntaxToken* _pDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_EXPRESSIONS_DELPHIENDOFMODULEEXPRESSIONSYNTAX_H
