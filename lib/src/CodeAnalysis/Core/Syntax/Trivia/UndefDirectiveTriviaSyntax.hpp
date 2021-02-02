#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class UndefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        LanguageSyntaxToken* startToken,
                                        LanguageSyntaxToken* undefKeyword,
                                        LanguageSyntaxToken* name,
                                        LanguageSyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~UndefDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* undefKeyword() const noexcept { return _pUndefKeyword; }
    inline virtual LanguageSyntaxToken* name() const noexcept { return _pName; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static UndefDirectiveTriviaSyntax* create(LanguageSyntaxToken* startToken,
                                              LanguageSyntaxToken* undefKeyword,
                                              LanguageSyntaxToken* name,
                                              LanguageSyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pUndefKeyword;
    LanguageSyntaxToken* _pName;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
