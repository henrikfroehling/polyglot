#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class MessageDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                          ISyntaxToken* startToken,
                                          ISyntaxToken* messageKeyword,
                                          ISyntaxToken* messageTypeToken,
                                          ISyntaxToken* messageLiteralToken,
                                          ISyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~MessageDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* messageKeyword() const noexcept { return _pMessageKeyword; }
    inline virtual ISyntaxToken* messageTypeToken() const noexcept { return _pMessageTypeToken; }
    inline virtual ISyntaxToken* messageLiteralToken() const noexcept { return _pMessageLiteralToken; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }
    inline pg_size childCount() const noexcept override { return _pMessageTypeToken != nullptr ? 5 : 4; }
    ISyntaxNode* child(pg_size index) const override;

    static MessageDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                                ISyntaxToken* startToken,
                                                ISyntaxToken* messageKeyword,
                                                ISyntaxToken* messageTypeToken,
                                                ISyntaxToken* messageLiteralToken,
                                                ISyntaxToken* endOfDirectiveToken) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pMessageKeyword;
    ISyntaxToken* _pMessageTypeToken; // optional
    ISyntaxToken* _pMessageLiteralToken;
    ISyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_MESSAGEDIRECTIVETRIVIASYNTAX_H
