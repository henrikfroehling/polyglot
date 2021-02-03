#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class MessageDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                          LanguageSyntaxToken* startToken,
                                          LanguageSyntaxToken* messageKeyword,
                                          LanguageSyntaxToken* messageTypeToken,
                                          LanguageSyntaxToken* messageLiteralToken,
                                          LanguageSyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~MessageDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* messageKeyword() const noexcept { return _pMessageKeyword; }
    inline virtual LanguageSyntaxToken* messageTypeToken() const noexcept { return _pMessageTypeToken; }
    inline virtual LanguageSyntaxToken* messageLiteralToken() const noexcept { return _pMessageLiteralToken; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }

    static MessageDirectiveTriviaSyntax* create(LanguageSyntaxToken* startToken,
                                                LanguageSyntaxToken* messageKeyword,
                                                LanguageSyntaxToken* messageTypeToken,
                                                LanguageSyntaxToken* messageLiteralToken,
                                                LanguageSyntaxToken* endOfDirectiveToken) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pMessageKeyword;
    LanguageSyntaxToken* _pMessageTypeToken; // optional
    LanguageSyntaxToken* _pMessageLiteralToken;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
