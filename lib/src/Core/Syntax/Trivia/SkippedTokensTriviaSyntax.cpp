#include "SkippedTokensTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

SkippedTokensTriviaSyntax::SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                                     std::vector<ISyntaxNode*> skippedTokens) noexcept
    : StructuredTriviaSyntax{syntaxKind},
      _skippedTokens{std::move(skippedTokens)}
{
    pg_size childNr{};

    for (ISyntaxNode* skippedToken : _skippedTokens)
    {
        adjustWidthAndFlags(skippedToken);
        skippedToken->setChildNumber(childNr++);
    }
}

} // end namespace polyglot::Core::Syntax
