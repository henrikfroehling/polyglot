#include "Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::Core::Syntax
{

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           pg_string_view text,
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

pg_string SyntaxTrivia::toString() const noexcept
{
    pg_stringstream str;
    str << L"Trivia(Position: " << _position << L", Kind: " << syntaxKindName(_syntaxKind) << L", Value: \"" << _text << L"\", Width: " << width() << L")";
    return str.str();
}

pg_string SyntaxTrivia::toShortString() const noexcept
{
    pg_stringstream str;

    if (_isLeading)
        str << L"Lead: ";
    else if (_isTrailing)
        str << L"Trail: ";

    str << L"Trivia: " << syntaxKindName(_syntaxKind) << L" " << span();
    return str.str();
}

} // end namespace polyglot::Core::Syntax
