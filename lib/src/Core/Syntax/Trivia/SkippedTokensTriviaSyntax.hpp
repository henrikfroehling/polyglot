#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H

#include <vector>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "StructuredTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;

class SkippedTokensTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                       std::vector<ISyntaxNode*> skippedTokens) noexcept;

    virtual ~SkippedTokensTriviaSyntax() noexcept = default;
    inline const std::vector<ISyntaxNode*>& skippedTokens() const noexcept { return _skippedTokens; }
    inline pg_size childCount() const noexcept override { return _skippedTokens.size(); }
    inline ISyntaxNode* child(pg_size index) const override { return _skippedTokens[index]; }

private:
    std::vector<ISyntaxNode*> _skippedTokens;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
