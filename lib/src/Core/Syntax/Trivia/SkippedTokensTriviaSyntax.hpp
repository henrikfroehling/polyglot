#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H

#include <vector>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class SkippedTokensTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                       std::vector<SyntaxVariant>&& skippedTokens) noexcept;

    virtual ~SkippedTokensTriviaSyntax() noexcept {}
    inline const std::vector<SyntaxVariant>& skippedTokens() const noexcept { return _skippedTokens; }
    inline bool isSkippedTokensTrivia() const noexcept override final { return true; }
    inline pg_size childCount() const noexcept override final { return _skippedTokens.size(); }
    inline SyntaxVariant child(pg_size index) const override final { return _skippedTokens[index]; }

    inline virtual pg_string typeName() const noexcept override { return L"SkippedTokensTriviaSyntax"; }

private:
    std::vector<SyntaxVariant> _skippedTokens;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
