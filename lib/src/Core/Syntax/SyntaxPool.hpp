#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXPOOL_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxPool final
{
public:
    SyntaxPool() noexcept;
    SyntaxPool(SyntaxPool&& other) noexcept;
    SyntaxPool& operator=(SyntaxPool&& other) noexcept;

    ISyntaxList* createSyntaxList() noexcept;
    ISyntaxList* createSyntaxList(std::vector<SyntaxVariant>&& nodes) noexcept;

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

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXPOOL_H
