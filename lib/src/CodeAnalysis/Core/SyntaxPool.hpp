#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "Syntax/LanguageSyntaxList.hpp"
#include "Syntax/LanguageSyntaxNode.hpp"
#include "Syntax/LanguageSyntaxToken.hpp"
#include "Syntax/LanguageSyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;

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

private:
    std::vector<UniquePtr<LanguageSyntaxNode>> _languageSyntaxNodes;
    std::vector<UniquePtr<LanguageSyntaxToken>> _languageSyntaxTokens;
    std::vector<UniquePtr<LanguageSyntaxTrivia>> _languageSyntaxTrivia;
    std::vector<UniquePtr<LanguageSyntaxList>> _languageSyntaxLists;
    std::vector<UniquePtr<ISyntaxTrivia>> _syntaxTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
