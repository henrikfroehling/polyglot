#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class MessageDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                          SyntaxToken* startToken,
                                          SyntaxToken* messageKeyword,
                                          SyntaxToken* messageTypeToken,
                                          SyntaxToken* messageLiteralToken,
                                          SyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~MessageDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* messageKeyword() const noexcept { return _pMessageKeyword; }
    inline virtual SyntaxToken* messageTypeToken() const noexcept { return _pMessageTypeToken; }
    inline virtual SyntaxToken* messageLiteralToken() const noexcept { return _pMessageLiteralToken; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }

    static MessageDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                                SyntaxToken* messageKeyword,
                                                SyntaxToken* messageTypeToken,
                                                SyntaxToken* messageLiteralToken,
                                                SyntaxToken* endOfDirectiveToken) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pMessageKeyword;
    SyntaxToken* _pMessageTypeToken; // optional
    SyntaxToken* _pMessageLiteralToken;
    SyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
