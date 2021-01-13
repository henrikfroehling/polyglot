#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia() noexcept
    : _syntaxKind{SyntaxKind::None},
      _position{},
      _text{},
      _pParent{nullptr}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind) noexcept
    : _syntaxKind{syntaxKind},
      _position{},
      _text{},
      _pParent{nullptr}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text,
                           pg_size position) noexcept
    : _syntaxKind{syntaxKind},
      _position{position},
      _text{text},
      _pParent{nullptr}
{}

SyntaxTrivia::~SyntaxTrivia() noexcept
{}

} // end namespace polyglot::CodeAnalysis
