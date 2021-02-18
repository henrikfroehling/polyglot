#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXLIST_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXLIST_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ISyntaxList : public ISyntaxNode
{
public:
    virtual ~ISyntaxList() noexcept = default;

    virtual ISyntaxNode* first() const = 0;
    virtual ISyntaxNode* last() const = 0;

protected:
    ISyntaxList() noexcept = default;
    ISyntaxList(const ISyntaxList&) noexcept = default;
    ISyntaxList(ISyntaxList&&) noexcept = default;
    ISyntaxList& operator=(const ISyntaxList&) noexcept = default;
    ISyntaxList& operator=(ISyntaxList&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXLIST_H
