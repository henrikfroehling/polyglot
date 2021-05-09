#include "SkippedTokensTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

SkippedTokensTriviaSyntax::SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                                     std::vector<SyntaxNodeOrToken>&& skippedTokens) noexcept
    : StructuredTriviaSyntax{syntaxKind},
      _skippedTokens{std::move(skippedTokens)}
{
    pg_size childNr{};

    for (SyntaxNodeOrToken& skippedNodeOrToken : _skippedTokens)
    {
        if (skippedNodeOrToken.isNode())
            adjustWidth(skippedNodeOrToken.node);
        else if (skippedNodeOrToken.isToken())
            adjustWidth(skippedNodeOrToken.token);
    }
}

} // end namespace polyglot::Core::Syntax
