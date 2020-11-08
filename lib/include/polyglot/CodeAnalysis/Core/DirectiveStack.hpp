#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H

#include <stack>
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

class POLYGLOT_API DirectiveStack
{
public:
    DirectiveStack() noexcept;
    explicit DirectiveStack(std::stack<DirectivePtr> directives) noexcept;
    inline bool isEmpty() const noexcept { return _directives.size() == 0; }
    bool isPreviousBranchTaken() const noexcept;
    bool hasUnfinishedIf() const noexcept;
    bool hasPreviousIfOrElseIf() const noexcept;
    bool hasUnfinishedRegion() const noexcept;
    DefineState isDefined(std::string_view id) const noexcept;

private:
    std::stack<DirectivePtr> _directives;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DIRECTIVESTACK_H
