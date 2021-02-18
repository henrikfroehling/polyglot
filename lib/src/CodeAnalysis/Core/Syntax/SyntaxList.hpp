#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXLIST_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXLIST_H

#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxList.hpp"
#include "SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;

class SyntaxList : public SyntaxNode, public ISyntaxList
{
public:
    SyntaxList() noexcept;
    explicit SyntaxList(std::vector<ISyntaxNode*>&& children) noexcept;
    virtual ~SyntaxList() noexcept;

    SyntaxList(const SyntaxList&) noexcept = default;
    SyntaxList(SyntaxList&&) noexcept = default;
    SyntaxList& operator=(const SyntaxList&) noexcept = default;
    SyntaxList& operator=(SyntaxList&&) noexcept = default;

    inline pg_size childCount() const noexcept override { return _children.size(); }
    inline ISyntaxNode* child(pg_size index) const override { return _children[index]; }
    inline ISyntaxNode* first() const noexcept override final { return _children.size() > 0 ? _children[0] : nullptr; }
    inline ISyntaxNode* last() const noexcept override final { return _children.size() > 0 ? _children.back() : nullptr; }
    void add(ISyntaxNode* node) noexcept;

protected:
    std::vector<ISyntaxNode*> _children;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXLIST_H
