#include "Core/Syntax/SyntaxMissingToken.hpp"
#include <sstream>
#include "Core/Syntax/SyntaxFlags.hpp"

namespace polyglot::Core::Syntax
{

SyntaxMissingToken::SyntaxMissingToken(SyntaxKind syntaxKind,
                                       std::string_view text,
                                       pg_size position,
                                       pg_size fullWidth,
                                       ISyntaxTriviaList* leadingTrivia,
                                       ISyntaxTriviaList* trailingTrivia,
                                       ISyntaxNode* parent) noexcept
    : SyntaxToken{syntaxKind, text, position, fullWidth, leadingTrivia, trailingTrivia, parent}
{
    _flags |= SyntaxFlags::IsMissing;
}

std::string SyntaxMissingToken::toString() const noexcept
{
    std::stringstream str;
    str << "MissingToken(" << _position << ", " << syntaxKindName(_syntaxKind) << ", \"" << _text << "\"" << "," << width() << ")";
    return str.str();
}

} // end namespace polyglot::Core::Syntax
