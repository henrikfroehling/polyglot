#include "CodeAnalysis/Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

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

LanguageSyntaxNode* MessageDirectiveTriviaSyntax::child(pg_size index) const
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
                                                                   LanguageSyntaxToken* startToken,
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

    return static_cast<MessageDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrMessageDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
