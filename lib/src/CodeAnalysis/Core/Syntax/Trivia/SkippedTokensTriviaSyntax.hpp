#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H

#include <vector>
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxNode;

class SkippedTokensTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit SkippedTokensTriviaSyntax(SyntaxKind syntaxKind,
                                       std::vector<LanguageSyntaxNode*> skippedTokens) noexcept;

    virtual ~SkippedTokensTriviaSyntax() noexcept = default;
    inline const std::vector<LanguageSyntaxNode*>& skippedTokens() const noexcept { return _skippedTokens; }
    inline LanguageSyntaxNode* child(pg_size index) const override { return _skippedTokens[index]; }
    inline pg_size childCount() const noexcept override { return _skippedTokens.size(); }

private:
    std::vector<LanguageSyntaxNode*> _skippedTokens;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SKIPPEDTOKENSTRIVIASYNTAX_H
