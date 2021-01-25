#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class LanguageSyntaxTrivia;

class SyntaxPool final
{
public:
    SyntaxPool() noexcept;

    SyntaxPool(const SyntaxPool&) noexcept = default;
    SyntaxPool(SyntaxPool&&) noexcept = default;
    SyntaxPool& operator=(const SyntaxPool&) noexcept = default;
    SyntaxPool& operator=(SyntaxPool&&) noexcept = default;

    LanguageSyntaxNode* createSyntaxNode() noexcept;

    LanguageSyntaxToken* createSyntaxToken(SyntaxKind syntaxKind,
                                           std::string_view text,
                                           pg_size position = 0) noexcept;

    LanguageSyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                             std::string_view text,
                                             pg_size position = 0) noexcept;

private:
    std::vector<UniquePtr<LanguageSyntaxNode>> _syntaxNodes;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
