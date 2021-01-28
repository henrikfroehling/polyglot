#include "CodeAnalysis/Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

MessageDirectiveTriviaSyntax::MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                           LanguageSyntaxToken* startToken,
                                                           LanguageSyntaxToken* messageKeyword,
                                                           LanguageSyntaxToken* messageTypeToken,
                                                           LanguageSyntaxToken* messageLiteralToken,
                                                           LanguageSyntaxToken* endOfDirectiveToken) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pMessageKeyword{messageKeyword},
      _pMessageTypeToken{messageTypeToken},
      _pMessageLiteralToken{messageLiteralToken},
      _pEndOfDirectiveToken{endOfDirectiveToken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pMessageKeyword);
    adjustWidthAndFlags(_pMessageTypeToken);
    adjustWidthAndFlags(_pMessageLiteralToken);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

MessageDirectiveTriviaSyntax* MessageDirectiveTriviaSyntax::create(LanguageSyntaxToken* startToken,
                                                                   LanguageSyntaxToken* messageKeyword,
                                                                   LanguageSyntaxToken* messageTypeToken,
                                                                   LanguageSyntaxToken* messageLiteralToken,
                                                                   LanguageSyntaxToken* endOfDirectiveToken) noexcept
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
