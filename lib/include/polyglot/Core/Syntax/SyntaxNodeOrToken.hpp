#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXNODEORTOKEN_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXNODEORTOKEN_H

#include "polyglot/polyglot_global.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;

struct POLYGLOT_API SyntaxNodeOrToken
{
    ISyntaxNode* node;
    ISyntaxToken* token;

    inline bool isNode() const noexcept { return node != nullptr; }
    inline bool isToken() const noexcept { return token != nullptr; }
    inline bool isEmpty() const noexcept { return !isNode() && !isToken(); }

    inline static SyntaxNodeOrToken asToken(ISyntaxToken* token) noexcept { return SyntaxNodeOrToken{nullptr, token}; }

    inline static SyntaxNodeOrToken asNode(ISyntaxNode* node) noexcept { return SyntaxNodeOrToken{node, nullptr}; }

    inline static SyntaxNodeOrToken empty() noexcept { return SyntaxNodeOrToken{nullptr, nullptr}; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXNODEORTOKEN_H
