#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H

#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Directive.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveList.hpp"

namespace polyglot::CodeAnalysis
{

enum class DefineState
{
    Defined,
    Undefined,
    Unspecified
};

class DirectiveStack
{
public:
    DirectiveStack() noexcept;
    DirectiveStack(const DirectiveStack&) noexcept = default;
    DirectiveStack(DirectiveStack&&) noexcept = default;
    DirectiveStack& operator=(const DirectiveStack&) noexcept = default;
    DirectiveStack& operator=(DirectiveStack&&) noexcept = default;
    DirectiveStack add(Directive* directive) noexcept;
    inline bool isEmpty() const noexcept { return _directives != nullptr && _directives->head() == nullptr && _directives->tail() == nullptr; }
    bool isPreviousBranchTaken() const noexcept;
    bool hasUnfinishedIf() const noexcept;
    bool hasPreviousIfOrElseIf() const noexcept;
    bool hasUnfinishedRegion() const noexcept;
    DefineState isDefined(std::string_view id) const noexcept;
    inline static DirectiveStack empty() noexcept { return DirectiveStack{DirectiveList::empty()}; }

private:
    explicit DirectiveStack(SharedPtr<DirectiveList> directives) noexcept;
    SharedPtr<DirectiveList> previousIf() const noexcept;
    SharedPtr<DirectiveList> previousIfElseIfElseOrRegion() const noexcept;
    SharedPtr<DirectiveList> previousRegion() const noexcept;

    SharedPtr<DirectiveList> completeIf(SharedPtr<DirectiveList> stack,
                                        bool& include) noexcept;

    SharedPtr<DirectiveList> completeRegion(SharedPtr<DirectiveList> stack) noexcept;

private:
    SharedPtr<DirectiveList> _directives;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
