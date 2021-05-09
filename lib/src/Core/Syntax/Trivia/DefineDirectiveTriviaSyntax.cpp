#include "DefineDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

DefineDirectiveTriviaSyntax::DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         ISyntaxToken* startToken,
                                                         ISyntaxToken* defineKeyword,
                                                         ISyntaxToken* name,
                                                         ISyntaxToken* endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pDefineKeyword{defineKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidth(_pStartToken);
    adjustWidth(_pDefineKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxNodeOrToken DefineDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxNodeOrToken::asToken(_pStartToken);
        case 1: return SyntaxNodeOrToken::asToken(_pDefineKeyword);
        case 2: return SyntaxNodeOrToken::asToken(_pName);
        case 3: return SyntaxNodeOrToken::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DefineDirectiveTriviaSyntax* DefineDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 ISyntaxToken* startToken,
                                                                 ISyntaxToken* defineKeyword,
                                                                 ISyntaxToken* name,
                                                                 ISyntaxToken* endOfDirectiveToken,
                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(defineKeyword != nullptr);
    assert(defineKeyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrDefineDirectiveTrivia = std::make_unique<DefineDirectiveTriviaSyntax>(SyntaxKind::DefineDirectiveTrivia, startToken,
                                                                                  defineKeyword, name, endOfDirectiveToken, isActive);

    return dynamic_cast<DefineDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrDefineDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
