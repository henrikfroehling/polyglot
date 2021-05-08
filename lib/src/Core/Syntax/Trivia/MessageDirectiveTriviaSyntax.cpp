#include "MessageDirectiveTriviaSyntax.hpp"
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
    adjustWidthAndFlags(_pStartToken);
    _pStartToken->setChildNumber(0);
    adjustWidthAndFlags(_pMessageKeyword);
    _pMessageKeyword->setChildNumber(1);
    adjustWidthAndFlags(_pMessageTypeToken);

    pg_size childNr{2};

    if (_pMessageTypeToken != nullptr)
        _pMessageTypeToken->setChildNumber(childNr++);

    adjustWidthAndFlags(_pMessageLiteralToken);
    _pMessageLiteralToken->setChildNumber(childNr++);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
    _pEndOfDirectiveToken->setChildNumber(childNr);
}

ISyntaxNode* MessageDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 4:
        {
            switch (index)
            {
                case 0: return _pStartToken;
                case 1: return _pMessageKeyword;
                case 2: return _pMessageLiteralToken;
                case 3: return _pEndOfDirectiveToken;
            }
        }
        case 5:
        {
            switch (index)
            {
                case 0: return _pStartToken;
                case 1: return _pMessageKeyword;
                case 2: return _pMessageTypeToken;
                case 3: return _pMessageLiteralToken;
                case 4: return _pEndOfDirectiveToken;
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
