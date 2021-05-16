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
      _pToken{token},
      _isLeading{false},
      _isTrailing{false}
{}

std::string SyntaxTrivia::toString() const noexcept
{
    std::stringstream str;
    str << "Trivia(Position: " << _position << ", Kind: " << syntaxKindName(_syntaxKind) << ", Value: \"" << _text << "\"" << ", Width: " << width() << ")";
    return str.str();
}

std::string SyntaxTrivia::toShortString() const noexcept
{
    std::stringstream str;

    if (_isLeading)
        str << "Lead: ";
    else if (_isTrailing)
        str << "Trail: ";

    str << "Trivia: " << syntaxKindName(_syntaxKind) << " " << span();
    return str.str();
}

} // end namespace polyglot::Core::Syntax
