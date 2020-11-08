#include "polyglot/CodeAnalysis/Delphi/DirectiveStack.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveStack::DirectiveStack() noexcept
    : _directives{}
{}

bool DirectiveStack::isPreviousBranchTaken() const noexcept
{
    return false;
}

bool DirectiveStack::hasUnfinishedIf() const noexcept
{
    return false;
}

bool DirectiveStack::hasPreviousIfOrElseIf() const noexcept
{
    return false;
}

bool DirectiveStack::hasUnfinishedRegion() const noexcept
{
    return false;
}

DefineState DirectiveStack::isDefined(std::string_view id) const noexcept
{
    return DefineState::Unspecified;
}

} // end namespace polyglot::CodeAnalysis
