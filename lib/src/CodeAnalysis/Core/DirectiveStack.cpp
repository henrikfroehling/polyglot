#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveStack::DirectiveStack() noexcept
    : _directives{nullptr}
{}

DirectiveStack::DirectiveStack(SharedPtr<DirectiveList> directives) noexcept
    : _directives{std::move(directives)}
{}

DirectiveStack DirectiveStack::add(Directive* directive) noexcept
{
    switch (directive->syntaxKind())
    {
        case SyntaxKind::EndIfDirectiveTrivia:
        {
            SharedPtr<DirectiveList> prevIf = previousIf();

            if (prevIf == nullptr || !prevIf->any())
                goto defaultCase;

            bool tmp{};
            return DirectiveStack{completeIf(_directives, tmp)};
        }
        case SyntaxKind::EndRegionDirectiveTrivia:
        {
            SharedPtr<DirectiveList> prevRegion = previousRegion();

            if (prevRegion == nullptr || !prevRegion->any())
                goto defaultCase;

            return DirectiveStack{completeRegion(_directives)};
        }
        default:
defaultCase:
            return DirectiveStack{ DirectiveList::create(directive, _directives != nullptr ? std::move(_directives) : DirectiveList::empty()) };
    }
}

bool DirectiveStack::isPreviousBranchTaken() const noexcept
{
    for (SharedPtr<DirectiveList> current = _directives; current != nullptr && current->any(); current = current->tail())
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
    SharedPtr<DirectiveList> previous = previousIfElseIfElseOrRegion();
    return previous != nullptr && previous->any() && previous->head()->syntaxKind() != SyntaxKind::RegionDirectiveTrivia;
}

bool DirectiveStack::hasPreviousIfOrElseIf() const noexcept
{
    SharedPtr<DirectiveList> previous = previousIfElseIfElseOrRegion();

    if (previous != nullptr && previous->any())
    {
        const SyntaxKind headSyntaxKind = previous->head()->syntaxKind();
        return headSyntaxKind == SyntaxKind::IfDirectiveTrivia || headSyntaxKind == SyntaxKind::ElseIfDirectiveTrivia;
    }

    return false;
}

bool DirectiveStack::hasUnfinishedRegion() const noexcept
{
    SharedPtr<DirectiveList> previous = previousIfElseIfElseOrRegion();
    return previous != nullptr && previous->any() && previous->head()->syntaxKind() == SyntaxKind::RegionDirectiveTrivia;
}

DefineState DirectiveStack::isDefined(std::string_view id) const noexcept
{
    for (SharedPtr<DirectiveList> current = _directives; current != nullptr && current->any(); current = current->tail())
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

SharedPtr<DirectiveList> DirectiveStack::previousIf() const noexcept
{
    SharedPtr<DirectiveList> current = _directives;

    while (current != nullptr && current->any())
    {
        if (current->head()->syntaxKind() == SyntaxKind::IfDirectiveTrivia)
            return current;

        current = current->tail();
    }

    return current;
}

SharedPtr<DirectiveList> DirectiveStack::previousIfElseIfElseOrRegion() const noexcept
{
    SharedPtr<DirectiveList> current = _directives;

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

SharedPtr<DirectiveList> DirectiveStack::previousRegion() const noexcept
{
    SharedPtr<DirectiveList> current = _directives;

    while (current != nullptr && current->any() && current->head()->syntaxKind() != SyntaxKind::RegionDirectiveTrivia)
        current = current->tail();

    return current;
}

SharedPtr<DirectiveList> DirectiveStack::completeIf(SharedPtr<DirectiveList> stack,
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

    SharedPtr<DirectiveList> newStack = completeIf(stack->tail(), include);

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

SharedPtr<DirectiveList> DirectiveStack::completeRegion(SharedPtr<DirectiveList> stack) noexcept
{
    if (!stack->any())
        return stack;

    if (stack->head()->syntaxKind() == SyntaxKind::RegionDirectiveTrivia)
        return stack->tail();

    SharedPtr<DirectiveList> newStack = completeRegion(stack->tail());
    newStack = DirectiveList::create(stack->head(), newStack);
    return newStack;
}

} // end namespace polyglot::CodeAnalysis
