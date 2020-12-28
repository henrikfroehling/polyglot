#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : SyntaxNode{SyntaxKind::None},
      _text{}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text,
                         pg_size position) noexcept
    : SyntaxNode{syntaxKind, position},
      _text{text}
{
    _fullWidth = _text.length();
}

bool SyntaxToken::value() const noexcept
{
    switch (_syntaxKind)
    {
        case SyntaxKind::TrueKeyword: return true;
        case SyntaxKind::FalseKeyword: return false;
    }

    return false;
}

} // end namespace polyglot::CodeAnalysis
