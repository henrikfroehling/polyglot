#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxTrivia.hpp"
#include "Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;
class LanguageSyntaxList;
class LanguageSyntaxToken;
class LanguageSyntaxTrivia;

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
                                                  pg_size position = 0,
                                                  LanguageSyntaxList* leadingTrivia = nullptr,
                                                  LanguageSyntaxList* trailingTrivia = nullptr) noexcept;

    static LanguageSyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                                    std::string_view text,
                                                    pg_size position = 0) noexcept;

    static ISyntaxTrivia* createSyntaxTrivia(LanguageSyntaxTrivia* trivia,
                                             ISyntaxToken* token) noexcept;

    static LanguageSyntaxList* createSyntaxList(std::vector<LanguageSyntaxNode*>&& nodes) noexcept;

    static LanguageSyntaxNode* addSyntaxNode(UniquePtr<LanguageSyntaxNode> syntaxNode) noexcept;
    static LanguageSyntaxToken* addSyntaxToken(UniquePtr<LanguageSyntaxToken> syntaxToken) noexcept;
    static LanguageSyntaxTrivia* addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia> syntaxTrivia) noexcept;
    static LanguageSyntaxList* addSyntaxList(UniquePtr<LanguageSyntaxList> syntaxList) noexcept;

private:
    static inline std::vector<UniquePtr<LanguageSyntaxNode>> _syntaxNodes{};
    static inline std::vector<UniquePtr<ISyntaxTrivia>> _syntaxTrivia{};
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
