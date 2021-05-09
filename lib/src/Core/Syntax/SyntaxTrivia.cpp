#include "SyntaxTrivia.hpp"

namespace polyglot::Core::Syntax
{

SyntaxTrivia::SyntaxTrivia() noexcept
    : ISyntaxTrivia{},
      _position{},
      _width{},
      _syntaxKind{SyntaxKind::None},
      _text{},
      _pToken{nullptr}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text,
                           pg_size position,
                           pg_size fullWidth,
                           ISyntaxToken* token) noexcept
    : ISyntaxTrivia{},
      _position{position},
      _width{width},
      _syntaxKind{syntaxKind},
      _text{text},
      _pToken{token}
{}

} // end namespace polyglot::Core::Syntax
