#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXVARIANT_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXVARIANT_H

#include "polyglot/polyglot_global.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxList;
class ISyntaxNode;
class ISyntaxToken;
class ISyntaxTrivia;

struct POLYGLOT_API SyntaxVariant
{
    ISyntaxList* list;
    ISyntaxNode* node;
    ISyntaxToken* token;
    ISyntaxTrivia* trivia;

    inline bool isList() const noexcept { return list != nullptr; }
    inline bool isNode() const noexcept { return node != nullptr; }
    inline bool isToken() const noexcept { return token != nullptr; }
    inline bool isTrivia() const noexcept { return trivia != nullptr; }
    inline bool isEmpty() const noexcept { return !isList() && !isNode() && !isToken() && !isTrivia(); }

    inline static SyntaxVariant asList(ISyntaxList* list) noexcept { return SyntaxVariant{list, nullptr, nullptr, nullptr}; }

    inline static SyntaxVariant asNode(ISyntaxNode* node) noexcept { return SyntaxVariant{nullptr, node, nullptr, nullptr}; }

    inline static SyntaxVariant asToken(ISyntaxToken* token) noexcept { return SyntaxVariant{nullptr, nullptr, token, nullptr}; }

    inline static SyntaxVariant asTrivia(ISyntaxTrivia* trivia) noexcept { return SyntaxVariant{nullptr, nullptr, nullptr, trivia}; }

    inline static SyntaxVariant empty() noexcept { return SyntaxVariant{nullptr, nullptr, nullptr, nullptr}; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXVARIANT_H
