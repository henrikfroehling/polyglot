#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVELIST_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVELIST_H

#include <memory>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Directive.hpp"

namespace polyglot::CodeAnalysis
{

class DirectiveList : public std::enable_shared_from_this<DirectiveList>
{
public:
    DirectiveList() noexcept;

    explicit DirectiveList(Directive* head,
                           SharedPtr<DirectiveList> tail) noexcept;

    inline Directive* head() const noexcept { return _ptrHead; }
    inline const SharedPtr<DirectiveList>& tail() const noexcept { return _ptrTail; }
    inline SharedPtr<DirectiveList> push(Directive* value) noexcept { return std::make_shared<DirectiveList>(value, shared_from_this()); }
    bool any() const noexcept;
    static SharedPtr<DirectiveList> empty() noexcept;

    static SharedPtr<DirectiveList> create(Directive* directive,
                                           SharedPtr<DirectiveList> tail) noexcept;

    friend bool operator==(const DirectiveList& lhs,
                           const DirectiveList& rhs) noexcept;

    friend bool operator!=(const DirectiveList& lhs,
                           const DirectiveList& rhs) noexcept;

private:
    Directive* _ptrHead;
    SharedPtr<DirectiveList> _ptrTail;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DIRECTIVELIST_H
