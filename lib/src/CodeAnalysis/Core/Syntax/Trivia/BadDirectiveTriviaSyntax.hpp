#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class BadDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                      LanguageSyntaxToken* startToken,
                                      LanguageSyntaxToken* identifier,
                                      LanguageSyntaxToken* endOfDirectiveToken,
                                      bool isActive) noexcept;

    virtual ~BadDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static BadDirectiveTriviaSyntax* create(LanguageSyntaxToken* startToken,
                                            LanguageSyntaxToken* identifier,
                                            LanguageSyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pIdentifier;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
