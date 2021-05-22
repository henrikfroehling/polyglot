#include "Core/Syntax/SyntaxMissingToken.hpp"
#include "Core/Syntax/SyntaxFlags.hpp"

namespace polyglot::Core::Syntax
{

SyntaxMissingToken::SyntaxMissingToken(SyntaxKind syntaxKind,
                                       pg_string_view text,
                                       pg_size position,
                                       pg_size fullWidth,
                                       ISyntaxTriviaList* leadingTrivia,
                                       ISyntaxTriviaList* trailingTrivia,
                                       ISyntaxNode* parent) noexcept
    : SyntaxToken{syntaxKind, text, position, fullWidth, leadingTrivia, trailingTrivia, parent}
{
    _flags |= SyntaxFlags::IsMissing;
}

pg_string SyntaxMissingToken::toString() const noexcept
{
    pg_stringstream str;
    str << L"MissingToken(" << _position << L", " << syntaxKindName(_syntaxKind) << L", \"" << _text << L"\", " << width() << L")";
    return str.str();
}

pg_string SyntaxMissingToken::toShortString() const noexcept
{
    pg_stringstream str;
    str << L"MissingToken: " << syntaxKindName(_syntaxKind) << L" " << fullSpan();
    return str.str();
}

} // end namespace polyglot::Core::Syntax
