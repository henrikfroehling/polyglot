#include "polyglot/CodeAnalysis/Core/DirectiveList.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

static DirectiveListPtr EMPTY = []()
{
    return std::make_shared<DirectiveList>();
}();

DirectiveList::DirectiveList() noexcept
    : _ptrHead{ nullptr },
    _ptrTail{ nullptr }
{}

DirectiveList::DirectiveList(DirectivePtr head,
                             DirectiveListPtr tail) noexcept
    : _ptrHead{ std::move(head) },
    _ptrTail{ std::move(tail) }
{
    assert(_ptrTail != nullptr);
}

bool DirectiveList::any() const noexcept
{
    return *this != *EMPTY;
}

DirectiveListPtr DirectiveList::empty() noexcept
{
    return EMPTY;
}

DirectiveListPtr DirectiveList::create(DirectivePtr directive,
                                       DirectiveListPtr tail) noexcept
{
    return std::make_shared<DirectiveList>(std::move(directive), std::move(tail));
}

bool operator==(const DirectiveList& lhs,
                const DirectiveList& rhs) noexcept
{
    if (lhs._ptrHead != nullptr && rhs._ptrHead != nullptr)
        return *(lhs._ptrHead) == *(rhs._ptrHead) && *(lhs._ptrTail) == *(rhs._ptrTail);

    return false;
}

bool operator!=(const DirectiveList& lhs,
                const DirectiveList& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::CodeAnalysis
