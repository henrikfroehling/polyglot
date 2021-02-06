#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTrivia.hpp"
#include "Syntax/LanguageSyntaxNode.hpp"
#include "Syntax/LanguageSyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;
class LanguageSyntaxList;
class LanguageSyntaxToken;

class SyntaxPool final
{
public:
    SyntaxPool() noexcept;
    SyntaxPool(SyntaxPool&& other) noexcept;
    SyntaxPool& operator=(SyntaxPool&& other) noexcept;

    LanguageSyntaxNode* createSyntaxNode() noexcept;

    LanguageSyntaxToken* createSyntaxToken(SyntaxKind syntaxKind,
                                           std::string_view text,
                                           pg_size position = 0,
                                           LanguageSyntaxList * leadingTrivia = nullptr,
                                           LanguageSyntaxList * trailingTrivia = nullptr) noexcept;

    LanguageSyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                             std::string_view text,
                                             pg_size position = 0) noexcept;

    ISyntaxTrivia* createSyntaxTrivia(LanguageSyntaxTrivia* trivia,
                                      ISyntaxToken* token) noexcept;

    LanguageSyntaxList* createSyntaxList(std::vector<LanguageSyntaxNode*>&& nodes) noexcept;

    LanguageSyntaxNode* addSyntaxNode(UniquePtr<LanguageSyntaxNode>&& syntaxNode) noexcept;
    LanguageSyntaxToken* addSyntaxToken(UniquePtr<LanguageSyntaxToken>&& syntaxToken) noexcept;
    LanguageSyntaxTrivia* addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia>&& syntaxTrivia) noexcept;
    LanguageSyntaxList* addSyntaxList(UniquePtr<LanguageSyntaxList>&& syntaxList) noexcept;

    void reserve(pg_size count) noexcept;

private:
    std::vector<UniquePtr<LanguageSyntaxNode>> _syntaxNodes;
    std::vector<UniquePtr<ISyntaxTrivia>> _syntaxTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
