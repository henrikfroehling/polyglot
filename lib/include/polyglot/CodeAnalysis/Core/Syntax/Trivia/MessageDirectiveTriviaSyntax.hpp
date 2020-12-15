#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API MessageDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                          SyntaxToken* startToken,
                                          SyntaxToken* messageKeyword,
                                          SyntaxToken* messageTypeToken,
                                          SyntaxToken* messageLiteralToken,
                                          SyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~MessageDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _ptrStartToken; }
    inline virtual SyntaxToken* messageKeyword() const noexcept { return _ptrMessageKeyword; }
    inline virtual SyntaxToken* messageTypeToken() const noexcept { return _ptrMessageTypeToken; }
    inline virtual SyntaxToken* messageLiteralToken() const noexcept { return _ptrMessageLiteralToken; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }

    static MessageDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                                SyntaxToken* messageKeyword,
                                                SyntaxToken* messageTypeToken,
                                                SyntaxToken* messageLiteralToken,
                                                SyntaxToken* endOfDirectiveToken) noexcept;

private:
    SyntaxToken* _ptrStartToken;
    SyntaxToken* _ptrMessageKeyword;
    SyntaxToken* _ptrMessageTypeToken; // optional
    SyntaxToken* _ptrMessageLiteralToken;
    SyntaxToken* _ptrEndOfDirectiveToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
