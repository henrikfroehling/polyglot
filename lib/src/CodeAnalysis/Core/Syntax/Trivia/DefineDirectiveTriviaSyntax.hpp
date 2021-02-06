#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         LanguageSyntaxToken* startToken,
                                         LanguageSyntaxToken* defineKeyword,
                                         LanguageSyntaxToken* name,
                                         LanguageSyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~DefineDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* defineKeyword() const noexcept { return _pDefineKeyword; }
    inline virtual LanguageSyntaxToken* name() const noexcept { return _pName; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static DefineDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               LanguageSyntaxToken* startToken,
                                               LanguageSyntaxToken* defineKeyword,
                                               LanguageSyntaxToken* name,
                                               LanguageSyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pDefineKeyword;
    LanguageSyntaxToken* _pName;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
