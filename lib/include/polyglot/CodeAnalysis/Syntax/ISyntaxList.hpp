#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXLIST_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXLIST_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ISyntaxList : public virtual ISyntaxNode
{
public:
    virtual ~ISyntaxList() noexcept {}

    virtual ISyntaxNode* first() const = 0;
    virtual ISyntaxNode* last() const = 0;    
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXLIST_H
