#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxList.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTriviaList.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxPool final
{
public:
    SyntaxPool() noexcept;
    SyntaxPool(SyntaxPool&& other) noexcept;
    SyntaxPool& operator=(SyntaxPool&& other) noexcept;

    ISyntaxList* createSyntaxList() noexcept;
    ISyntaxList* createSyntaxList(std::vector<ISyntaxNode*>&& nodes) noexcept;

    ISyntaxNode* createSyntaxNode() noexcept;

    ISyntaxToken* createSyntaxToken(SyntaxKind syntaxKind,
                                    std::string_view text,
                                    pg_size position = 0,
                                    ISyntaxTriviaList* leadingTrivia = nullptr,
                                    ISyntaxTriviaList* trailingTrivia = nullptr,
                                    ISyntaxNode* parent = nullptr) noexcept;

    ISyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                      std::string_view text,
                                      pg_size position = 0,
                                      ISyntaxToken* token = nullptr) noexcept;

    ISyntaxTriviaList* createSyntaxTriviaList(ISyntaxToken* token = nullptr) noexcept;

    ISyntaxTriviaList* createSyntaxTriviaList(std::vector<ISyntaxTrivia*>&& trivia,
                                              ISyntaxToken* token = nullptr) noexcept;

    ISyntaxList* addSyntaxList(UniquePtr<ISyntaxList>&& syntaxList) noexcept;
    ISyntaxNode* addSyntaxNode(UniquePtr<ISyntaxNode>&& syntaxNode) noexcept;
    ISyntaxToken* addSyntaxToken(UniquePtr<ISyntaxToken>&& syntaxToken) noexcept;
    ISyntaxTrivia* addSyntaxTrivia(UniquePtr<ISyntaxTrivia>&& syntaxTrivia) noexcept;
    ISyntaxTriviaList* addSyntaxTriviaList(UniquePtr<ISyntaxTriviaList>&& syntaxTriviaList) noexcept;

private:
    std::vector<UniquePtr<ISyntaxList>> _syntaxLists;
    std::vector<UniquePtr<ISyntaxNode>> _syntaxNodes;
    std::vector<UniquePtr<ISyntaxToken>> _syntaxTokens;
    std::vector<UniquePtr<ISyntaxTrivia>> _syntaxTrivia;
    std::vector<UniquePtr<ISyntaxTriviaList>> _syntaxTriviaLists;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
