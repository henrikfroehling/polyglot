#ifndef POLYGLOT_CORE_SYNTAX_ISYNTAXLIST_H
#define POLYGLOT_CORE_SYNTAX_ISYNTAXLIST_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"

namespace polyglot::Core::Syntax
{

class POLYGLOT_API ISyntaxList : public ISyntaxNode
{
public:
    virtual ~ISyntaxList() noexcept {}

    virtual SyntaxNodeOrToken first() const noexcept = 0;
    virtual SyntaxNodeOrToken last() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_ISYNTAXLIST_H
