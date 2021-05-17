#include "Delphi/Syntax/Trivia/DelphiMessageDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiMessageDirectiveTriviaSyntax::DelphiMessageDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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
    {
        adjustWidth(_pMessageTypeToken);
        static_cast<SyntaxToken*>(_pMessageTypeToken)->setTriviaParent(this);
    }

    adjustWidth(_pMessageLiteralToken);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pMessageKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pMessageLiteralToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiMessageDirectiveTriviaSyntax::child(pg_size index) const
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

DelphiMessageDirectiveTriviaSyntax* DelphiMessageDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrMessageDirectiveTrivia = std::make_unique<DelphiMessageDirectiveTriviaSyntax>(SyntaxKind::MessageDirectiveTrivia, startToken, messageKeyword,
                                                                                          messageTypeToken, messageLiteralToken, endOfDirectiveToken);

    return static_cast<DelphiMessageDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrMessageDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
