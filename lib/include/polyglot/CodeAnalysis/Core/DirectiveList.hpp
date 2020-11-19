#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVELIST_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVELIST_H

#include <memory>
#include "polyglot/CodeAnalysis/Core/Directive.hpp"

namespace polyglot::CodeAnalysis
{

class DirectiveList;
using DirectiveListPtr = std::shared_ptr<DirectiveList>;

class DirectiveList : public std::enable_shared_from_this<DirectiveList>
{
public:
    DirectiveList() noexcept;
    explicit DirectiveList(DirectivePtr head,
                           DirectiveListPtr tail) noexcept;

    inline const DirectivePtr& head() const noexcept { return _ptrHead; }
    inline const DirectiveListPtr& tail() const noexcept { return _ptrTail; }
    inline DirectiveListPtr push(DirectivePtr value) noexcept { return std::make_shared<DirectiveList>(std::move(value), shared_from_this()); }
    bool any() const noexcept;
    static DirectiveListPtr empty() noexcept;

    static DirectiveListPtr create(DirectivePtr directive,
                                   DirectiveListPtr tail) noexcept;

    friend bool operator==(const DirectiveList& lhs,
                           const DirectiveList& rhs) noexcept;

    friend bool operator!=(const DirectiveList& lhs,
                           const DirectiveList& rhs) noexcept;

private:
    DirectivePtr _ptrHead;
    DirectiveListPtr _ptrTail;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DIRECTIVELIST_H
