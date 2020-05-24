#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : SyntaxNode{SyntaxKind::None},
    _position{},
    _text{}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind},
      _position{},
      _text{}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         pg_size position,
                         std::string text) noexcept
    : SyntaxNode{syntaxKind},
      _position{position},
      _text{text}
{}

} // end namespace polyglot::CodeAnalysis
