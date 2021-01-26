#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "Syntax/LanguageSyntaxNode.hpp"
#include "Syntax/LanguageSyntaxToken.hpp"
#include "Syntax/LanguageSyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxPool final
{
public:
    SyntaxPool() noexcept = default;

    SyntaxPool(const SyntaxPool&) noexcept = default;
    SyntaxPool(SyntaxPool&&) noexcept = default;
    SyntaxPool& operator=(const SyntaxPool&) noexcept = default;
    SyntaxPool& operator=(SyntaxPool&&) noexcept = default;

    static LanguageSyntaxNode* createSyntaxNode() noexcept;

    static LanguageSyntaxToken* createSyntaxToken(SyntaxKind syntaxKind,
                                                  std::string_view text,
                                                  pg_size position = 0) noexcept;

    static LanguageSyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                                    std::string_view text,
                                                    pg_size position = 0) noexcept;

    static LanguageSyntaxNode* addSyntaxNode(UniquePtr<LanguageSyntaxNode> syntaxNode) noexcept;
    static LanguageSyntaxToken* addSyntaxToken(UniquePtr<LanguageSyntaxToken> syntaxToken) noexcept;
    static LanguageSyntaxTrivia* addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia> syntaxTrivia) noexcept;

private:
    static inline std::vector<UniquePtr<LanguageSyntaxNode>> _syntaxNodes{};
    static inline std::vector<UniquePtr<LanguageSyntaxToken>> _syntaxTokens{};
    static inline std::vector<UniquePtr<LanguageSyntaxTrivia>> _syntaxTrivia{};
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
