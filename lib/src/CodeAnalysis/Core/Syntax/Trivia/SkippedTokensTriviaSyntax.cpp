#include "CodeAnalysis/Core/Syntax/Trivia/SkippedTokensTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

SkippedTokensTriviaSyntax::SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                                     std::vector<LanguageSyntaxToken*> skippedTokens) noexcept
    : StructuredTriviaSyntax{syntaxKind},
      _skippedTokens{std::move(skippedTokens)}
{}

} // end namespace polyglot::CodeAnalysis
