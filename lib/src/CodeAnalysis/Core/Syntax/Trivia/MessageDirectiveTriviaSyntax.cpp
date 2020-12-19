#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

MessageDirectiveTriviaSyntax::MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                           SyntaxToken* startToken,
                                                           SyntaxToken* messageKeyword,
                                                           SyntaxToken* messageTypeToken,
                                                           SyntaxToken* messageLiteralToken,
                                                           SyntaxToken* endOfDirectiveToken) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pMessageKeyword{messageKeyword},
      _pMessageTypeToken{messageTypeToken},
      _pMessageLiteralToken{messageLiteralToken},
      _pEndOfDirectiveToken{endOfDirectiveToken}
{
    _position = _pStartToken->position();
}

MessageDirectiveTriviaSyntax* MessageDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                                   SyntaxToken* messageKeyword,
                                                                   SyntaxToken* messageTypeToken,
                                                                   SyntaxToken* messageLiteralToken,
                                                                   SyntaxToken* endOfDirectiveToken) noexcept
{
    assert(startToken != nullptr);
    assert(messageKeyword != nullptr);
    assert(messageKeyword->syntaxKind() == SyntaxKind::MessageDirectiveKeyword);
    assert(messageLiteralToken != nullptr);
    assert(messageLiteralToken->syntaxKind() == SyntaxKind::SingleQuotationStringLiteralToken);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrMessageDirectiveTrivia = std::make_unique<MessageDirectiveTriviaSyntax>(SyntaxKind::MessageDirectiveTrivia, startToken, messageKeyword,
                                                                                    messageTypeToken, messageLiteralToken, endOfDirectiveToken);

    return static_cast<MessageDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrMessageDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
