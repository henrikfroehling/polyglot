#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H

#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxPool final
{
public:
    static Ptr<SyntaxNode> createSyntaxNode() noexcept;
    static Ptr<SyntaxToken> createSyntaxToken() noexcept;
    static Ptr<SyntaxTrivia> createSyntaxTrivia() noexcept;
    static Ptr<SyntaxNode> addSyntaxNode(UniquePtr<SyntaxNode> syntaxNode) noexcept;
    static Ptr<SyntaxToken> addSyntaxToken(UniquePtr<SyntaxToken> syntaxToken) noexcept;
    static Ptr<SyntaxTrivia> addSyntaxTrivia(UniquePtr<SyntaxTrivia> syntaxTrivia) noexcept;

private:
    static inline std::vector<UniquePtr<SyntaxNode>> _syntaxNodes{};
    static inline std::vector<UniquePtr<SyntaxToken>> _syntaxTokens{};
    static inline std::vector<UniquePtr<SyntaxTrivia>> _syntaxTrivia{};
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXPOOL_H
