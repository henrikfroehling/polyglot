#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXNODEORTOKEN_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXNODEORTOKEN_H

#include "polyglot/polyglot_global.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;

struct SyntaxNodeOrToken
{
    ISyntaxNode* node;
    ISyntaxToken* token;

    inline bool isNode() const noexcept { return node != nullptr; }
    inline bool isToken() const noexcept { return token != nullptr; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXNODEORTOKEN_H
