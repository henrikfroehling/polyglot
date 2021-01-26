#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFENDDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFENDDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class IfEndDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit IfEndDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        LanguageSyntaxToken* startToken,
                                        LanguageSyntaxToken* ifEndKeyword,
                                        LanguageSyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~IfEndDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* ifEndKeyword() const noexcept { return _pIfEndKeyword; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static IfEndDirectiveTriviaSyntax* create(LanguageSyntaxToken* startToken,
                                              LanguageSyntaxToken* ifEndKeyword,
                                              LanguageSyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pIfEndKeyword;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFENDDIRECTIVETRIVIASYNTAX_H
