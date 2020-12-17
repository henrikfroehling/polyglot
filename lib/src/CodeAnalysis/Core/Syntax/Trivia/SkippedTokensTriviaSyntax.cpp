#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/SkippedTokensTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

SkippedTokensTriviaSyntax::SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                                     std::vector<SyntaxNode*> skippedTokens) noexcept
    : StructuredTriviaSyntax{syntaxKind},
      _skippedTokens{std::move(skippedTokens)}
{
    if (_skippedTokens.size() > 0)
        _position = _skippedTokens[0]->position();
}

} // end namespace polyglot::CodeAnalysis
