#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class SwitchDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit SwitchDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         LanguageSyntaxToken* startToken,
                                         LanguageSyntaxToken* identifier,
                                         LanguageSyntaxToken* onOffToken,
                                         LanguageSyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~SwitchDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual LanguageSyntaxToken* onOffToken() const noexcept { return _pOnOffToken; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }

    static SwitchDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               LanguageSyntaxToken* startToken,
                                               LanguageSyntaxToken* identifier,
                                               LanguageSyntaxToken* onOffToken,
                                               LanguageSyntaxToken* endOfDirectiveToken) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pIdentifier;
    LanguageSyntaxToken* _pOnOffToken;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
