#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H

#include <forward_list>
#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Directive.hpp"

namespace polyglot::CodeAnalysis
{

enum class DefineState
{
    Defined,
    Undefined,
    Unspecified
};

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

class POLYGLOT_API DirectiveStack
{
public:
    DirectiveStack() noexcept;
    DirectiveStack add(DirectivePtr directive) noexcept;
    inline bool isEmpty() const noexcept { return _directives != nullptr && _directives->head() == nullptr && _directives->tail() == nullptr; }
    bool isPreviousBranchTaken() const noexcept;
    bool hasUnfinishedIf() const noexcept;
    bool hasPreviousIfOrElseIf() const noexcept;
    bool hasUnfinishedRegion() const noexcept;
    DefineState isDefined(std::string_view id) const noexcept;
    inline static DirectiveStack empty() noexcept { return DirectiveStack{DirectiveList::empty()}; }

private:
    explicit DirectiveStack(DirectiveListPtr directives) noexcept;
    DirectiveListPtr previousIf() const noexcept;
    DirectiveListPtr previousIfElseIfElseOrRegion() const noexcept;
    DirectiveListPtr previousRegion() const noexcept;

    DirectiveListPtr completeIf(DirectiveListPtr stack,
                                bool& include) noexcept;

    DirectiveListPtr completeRegion(DirectiveListPtr stack) noexcept;

private:
    DirectiveListPtr _directives;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
