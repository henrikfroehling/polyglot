#ifndef POLYGLOT_CORE_SYNTAX_ISYNTAXTREE_H
#define POLYGLOT_CORE_SYNTAX_ISYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/LanguageKind.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;

class POLYGLOT_API ISyntaxTree
{
public:
    virtual ~ISyntaxTree() noexcept {}

    virtual ISyntaxNode* root() const noexcept = 0;
    virtual LanguageKind languageKind() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_ISYNTAXTREE_H
