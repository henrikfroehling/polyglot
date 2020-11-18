#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

static DirectiveListPtr EMPTY = []()
{
    return std::make_shared<DirectiveList>();
}();

DirectiveList::DirectiveList() noexcept
    : _ptrHead{nullptr},
      _ptrTail{nullptr}
{}

DirectiveList::DirectiveList(DirectivePtr head,
                             DirectiveListPtr tail) noexcept
    : _ptrHead{std::move(head)},
      _ptrTail{std::move(tail)}
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

DirectiveStack::DirectiveStack() noexcept
    : _directives{nullptr}
{}

DirectiveStack::DirectiveStack(DirectiveListPtr directives) noexcept
    : _directives{std::move(directives)}
{}

DirectiveStack DirectiveStack::add(DirectivePtr directive) noexcept
{
    switch (directive->syntaxKind())
    {
        case SyntaxKind::EndIfDirectiveTrivia:
        {
            DirectiveListPtr prevIf = previousIf();

            if (prevIf == nullptr || !prevIf->any())
                goto defaultCase;

            bool tmp{};
            return DirectiveStack{completeIf(_directives, tmp)};
        }
        case SyntaxKind::EndRegionDirectiveTrivia:
        {
            DirectiveListPtr prevRegion = previousRegion();

            if (prevRegion == nullptr || !prevRegion->any())
                goto defaultCase;

            return DirectiveStack{completeRegion(_directives)};
        }
        default:
defaultCase:
            return DirectiveStack{DirectiveList::create(std::move(directive), _directives != nullptr ? std::move(_directives) : DirectiveList::empty())};
    }
}

bool DirectiveStack::isPreviousBranchTaken() const noexcept
{
    for (DirectiveListPtr current = _directives; current != nullptr && current->any(); current = current->tail())
    {
        if (current->head()->isBranchTaken())
            return true;
        else if (current->head()->syntaxKind() == SyntaxKind::IfDirectiveTrivia)
            return false;
    }

    return false;
}

bool DirectiveStack::hasUnfinishedIf() const noexcept
{
    DirectiveListPtr previous = previousIfElseIfElseOrRegion();
    return previous != nullptr && previous->any() && previous->head()->syntaxKind() != SyntaxKind::RegionDirectiveTrivia;
}

bool DirectiveStack::hasPreviousIfOrElseIf() const noexcept
{
    DirectiveListPtr previous = previousIfElseIfElseOrRegion();

    if (previous != nullptr && previous->any())
    {
        const SyntaxKind headSyntaxKind = previous->head()->syntaxKind();
        return headSyntaxKind == SyntaxKind::IfDirectiveTrivia || headSyntaxKind == SyntaxKind::ElseIfDirectiveTrivia;
    }

    return false;
}

bool DirectiveStack::hasUnfinishedRegion() const noexcept
{
    DirectiveListPtr previous = previousIfElseIfElseOrRegion();
    return previous != nullptr && previous->any() && previous->head()->syntaxKind() == SyntaxKind::RegionDirectiveTrivia;
}

DefineState DirectiveStack::isDefined(std::string_view id) const noexcept
{
    for (DirectiveListPtr current = _directives; current != nullptr && current->any(); current = current->tail())
    {
        switch (current->head()->syntaxKind())
        {
            case SyntaxKind::DefineDirectiveTrivia:
            {
                if (current->head()->identifier() == id)
                    return DefineState::Defined;

                break;
            }
            case SyntaxKind::UndefDirectiveTrivia:
            {
                if (current->head()->identifier() == id)
                    return DefineState::Undefined;

                break;
            }
            case SyntaxKind::ElseIfDirectiveTrivia:
            case SyntaxKind::ElseDirectiveTrivia:
            {
                do
                {
                    current = current->tail();

                    if (current == nullptr || !current->any())
                        return DefineState::Unspecified;
                }
                while (current->head()->syntaxKind() != SyntaxKind::IfDirectiveTrivia);

                break;
            }
        }
    }

    return DefineState::Unspecified;
}

DirectiveListPtr DirectiveStack::previousIf() const noexcept
{
    DirectiveListPtr current = _directives;

    while (current != nullptr && current->any())
    {
        if (current->head()->syntaxKind() == SyntaxKind::IfDirectiveTrivia)
            return current;

        current = current->tail();
    }

    return current;
}

DirectiveListPtr DirectiveStack::previousIfElseIfElseOrRegion() const noexcept
{
    DirectiveListPtr current = _directives;

    while (current != nullptr && current->any())
    {
        switch (current->head()->syntaxKind())
        {
            case SyntaxKind::IfDirectiveTrivia:
            case SyntaxKind::ElseIfDirectiveTrivia:
            case SyntaxKind::ElseDirectiveTrivia:
            case SyntaxKind::RegionDirectiveTrivia:
                return current;
        }

        current = current->tail();
    }

    return current;
}

DirectiveListPtr DirectiveStack::previousRegion() const noexcept
{
    DirectiveListPtr current = _directives;

    while (current != nullptr && current->any() && current->head()->syntaxKind() != SyntaxKind::RegionDirectiveTrivia)
        current = current->tail();

    return current;
}

DirectiveListPtr DirectiveStack::completeIf(DirectiveListPtr stack,
                                            bool& include) noexcept
{
    if (!stack->any())
    {
        include = true;
        return stack;
    }

    if (stack->head()->syntaxKind() == SyntaxKind::IfDirectiveTrivia)
    {
        include = stack->head()->isBranchTaken();
        return stack->tail();
    }

    DirectiveListPtr newStack = completeIf(stack->tail(), include);

    switch (stack->head()->syntaxKind())
    {
        case SyntaxKind::ElseIfDirectiveTrivia:
        case SyntaxKind::ElseDirectiveTrivia:
            include = stack->head()->isBranchTaken();
            break;
        default:
        {
            if (include)
                newStack = DirectiveList::create(stack->head(), newStack);

            break;
        }
    }

    return newStack;
}

DirectiveListPtr DirectiveStack::completeRegion(DirectiveListPtr stack) noexcept
{
    if (!stack->any())
        return stack;

    if (stack->head()->syntaxKind() == SyntaxKind::RegionDirectiveTrivia)
        return stack->tail();

    DirectiveListPtr newStack = completeRegion(stack->tail());
    newStack = DirectiveList::create(stack->head(), newStack);
    return newStack;
}

} // end namespace polyglot::CodeAnalysis
