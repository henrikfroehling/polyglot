#include "Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

MessageDirectiveTriviaSyntax::MessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                           ISyntaxToken* startToken,
                                                           ISyntaxToken* messageKeyword,
                                                           ISyntaxToken* messageTypeToken,
                                                           ISyntaxToken* messageLiteralToken,
                                                           ISyntaxToken* endOfDirectiveToken) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pMessageKeyword{messageKeyword},
      _pMessageTypeToken{messageTypeToken},
      _pMessageLiteralToken{messageLiteralToken},
      _pEndOfDirectiveToken{endOfDirectiveToken}
{
    _position = _pStartToken->position();
    adjustWidth(_pStartToken);
    adjustWidth(_pMessageKeyword);

    if (_pMessageTypeToken != nullptr)
        adjustWidth(_pMessageTypeToken);

    adjustWidth(_pMessageLiteralToken);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxVariant MessageDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 4:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pStartToken);
                case 1: return SyntaxVariant::asToken(_pMessageKeyword);
                case 2: return SyntaxVariant::asToken(_pMessageLiteralToken);
                case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
            }
        }
        case 5:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pStartToken);
                case 1: return SyntaxVariant::asToken(_pMessageKeyword);
                case 2: return SyntaxVariant::asToken(_pMessageTypeToken);
                case 3: return SyntaxVariant::asToken(_pMessageLiteralToken);
                case 4: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

MessageDirectiveTriviaSyntax* MessageDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                   ISyntaxToken* startToken,
                                                                   ISyntaxToken* messageKeyword,
                                                                   ISyntaxToken* messageTypeToken,
                                                                   ISyntaxToken* messageLiteralToken,
                                                                   ISyntaxToken* endOfDirectiveToken) noexcept
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

    return dynamic_cast<MessageDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrMessageDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
