#include "Core/Syntax/SyntaxTrivia.hpp"
#include <sstream>

namespace polyglot::Core::Syntax
{

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text,
                           pg_size position,
                           pg_size width,
                           ISyntaxToken* token) noexcept
    : ISyntaxTrivia{},
      _position{position},
      _width{width},
      _syntaxKind{syntaxKind},
      _text{text},
      _pToken{token}
{}

std::string SyntaxTrivia::toString() const noexcept
{
    std::stringstream str;
    str << "Trivia(" << _position << ", " << syntaxKindName(_syntaxKind) << ", \"" << _text << "\"" << "," << width() << ")";
    return str.str();
}

} // end namespace polyglot::Core::Syntax
