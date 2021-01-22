#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXLIST_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXLIST_H

#include <vector>
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxList : public LanguageSyntaxNode
{
public:
    LanguageSyntaxList() = delete;
    explicit LanguageSyntaxList(std::vector<LanguageSyntaxNode*>&& children) noexcept;
    virtual ~LanguageSyntaxList() noexcept;

    LanguageSyntaxList(const LanguageSyntaxList&) noexcept = default;
    LanguageSyntaxList(LanguageSyntaxList&&) noexcept = default;
    LanguageSyntaxList& operator=(const LanguageSyntaxList&) noexcept = default;
    LanguageSyntaxList& operator=(LanguageSyntaxList&&) noexcept = default;

    inline LanguageSyntaxNode* child(pg_size index) const noexcept override { return _children[index]; }
    inline pg_size childCount() const noexcept override { return _children.size(); }

protected:
    std::vector<LanguageSyntaxNode*> _children;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXLIST_H
