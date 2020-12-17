#include "polyglot/CodeAnalysis/Core/DirectiveList.hpp"
#include "polyglot/CodeAnalysis/Core/Directive.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

static SharedPtr<DirectiveList> EMPTY = []()
{
    return std::make_shared<DirectiveList>();
}();

DirectiveList::DirectiveList() noexcept
    : _pHead{nullptr},
      _ptrTail{nullptr}
{}

DirectiveList::DirectiveList(Directive* head,
                             SharedPtr<DirectiveList> tail) noexcept
    : _pHead{head},
      _ptrTail{std::move(tail)}
{
    assert(_ptrTail != nullptr);
}

bool DirectiveList::any() const noexcept
{
    return *this != *EMPTY;
}

SharedPtr<DirectiveList> DirectiveList::empty() noexcept
{
    return EMPTY;
}

SharedPtr<DirectiveList> DirectiveList::create(Directive* directive,
                                               SharedPtr<DirectiveList> tail) noexcept
{
    return std::make_shared<DirectiveList>(directive, std::move(tail));
}

bool operator==(const DirectiveList& lhs,
                const DirectiveList& rhs) noexcept
{
    if (lhs._pHead != nullptr && rhs._pHead != nullptr)
        return *(lhs._pHead) == *(rhs._pHead) && *(lhs._ptrTail) == *(rhs._ptrTail);

    return false;
}

bool operator!=(const DirectiveList& lhs,
                const DirectiveList& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::CodeAnalysis
