#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H

#include <string_view>
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
