#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H

#include <vector>
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class SkippedTokensTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                       std::vector<SyntaxToken*> skippedTokens) noexcept;

    virtual ~SkippedTokensTriviaSyntax() noexcept = default;
    inline const std::vector<SyntaxToken*>& skippedTokens() const noexcept { return _skippedTokens; }

private:
    std::vector<SyntaxToken*> _skippedTokens;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
