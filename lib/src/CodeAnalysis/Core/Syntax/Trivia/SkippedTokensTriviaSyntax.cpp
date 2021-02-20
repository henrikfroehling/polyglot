#include "CodeAnalysis/Core/Syntax/Trivia/SkippedTokensTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

SkippedTokensTriviaSyntax::SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                                     std::vector<ISyntaxNode*> skippedTokens) noexcept
    : StructuredTriviaSyntax{syntaxKind},
      _skippedTokens{std::move(skippedTokens)}
{
    for (ISyntaxNode* skippedToken : _skippedTokens)
        adjustWidthAndFlags(skippedToken);
}

} // end namespace polyglot::CodeAnalysis
