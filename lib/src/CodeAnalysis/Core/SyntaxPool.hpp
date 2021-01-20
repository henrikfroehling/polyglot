#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxPool final
{
public:
    static SyntaxNode* createSyntaxNode() noexcept;

    static SyntaxToken* createSyntaxToken(SyntaxKind syntaxKind,
                                          std::string_view text,
                                          pg_size position = 0) noexcept;

    static SyntaxTrivia* createSyntaxTrivia() noexcept;

    static SyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                            std::string_view text,
                                            pg_size position = 0) noexcept;

    static SyntaxNode* addSyntaxNode(UniquePtr<SyntaxNode> syntaxNode) noexcept;
    static SyntaxToken* addSyntaxToken(UniquePtr<SyntaxToken> syntaxToken) noexcept;
    static SyntaxTrivia* addSyntaxTrivia(UniquePtr<SyntaxTrivia> syntaxTrivia) noexcept;

private:
    static inline std::vector<UniquePtr<SyntaxNode>> _syntaxNodes{};
    static inline std::vector<UniquePtr<SyntaxToken>> _syntaxTokens{};
    static inline std::vector<UniquePtr<SyntaxTrivia>> _syntaxTrivia{};
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
