#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXVARIANT_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXVARIANT_H

#include "polyglot/polyglot_global.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxList;
class ISyntaxNode;
class ISyntaxToken;

struct POLYGLOT_API SyntaxVariant
{
    ISyntaxList* list;
    ISyntaxNode* node;
    ISyntaxToken* token;

    inline bool isList() const noexcept { return list != nullptr; }
    inline bool isNode() const noexcept { return node != nullptr; }
    inline bool isToken() const noexcept { return token != nullptr; }
    inline bool isEmpty() const noexcept { return !isList() && !isNode() && !isToken(); }

    inline static SyntaxVariant asList(ISyntaxList* list) noexcept { return SyntaxVariant{list, nullptr, nullptr}; }

    inline static SyntaxVariant asNode(ISyntaxNode* node) noexcept { return SyntaxVariant{nullptr, node, nullptr}; }

    inline static SyntaxVariant asToken(ISyntaxToken* token) noexcept { return SyntaxVariant{nullptr, nullptr, token}; }

    inline static SyntaxVariant empty() noexcept { return SyntaxVariant{nullptr, nullptr, nullptr}; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXVARIANT_H
