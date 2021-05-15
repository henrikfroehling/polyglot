#include "Core/Parser/DirectiveStack.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Parser/Directive.hpp"

namespace polyglot::Core::Parser
{

using namespace Core::Syntax;

DirectiveStack::DirectiveStack() noexcept
    : _directives{nullptr}
{}

DirectiveStack::DirectiveStack(SharedPtr<DirectiveList> directives) noexcept
    : _directives{std::move(directives)}
{}

DirectiveStack DirectiveStack::add(SharedPtr<Directive> directive) noexcept
{
    switch (directive->syntaxKind())
    {
        case SyntaxKind::EndIfDirectiveTrivia:
        {
            SharedPtr<DirectiveList> prevIf = previousIfOrIfN();

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
            return DirectiveStack{DirectiveList::create(std::move(directive), _directives != nullptr ? std::move(_directives) : DirectiveList::empty())};
    }
}

bool DirectiveStack::isPreviousBranchTaken() const noexcept
{
    for (SharedPtr<DirectiveList> current = _directives; current != nullptr && current->any() && current->head() != nullptr; current = current->tail())
    {
        switch (current->head()->syntaxKind())
        {
            case SyntaxKind::IfDirectiveTrivia:
            case SyntaxKind::IfDefDirectiveTrivia:
            case SyntaxKind::IfNDefDirectiveTrivia:
            case SyntaxKind::ElseIfDirectiveTrivia:
                return current->head()->isBranchTaken();
            default:
                return false;
        }
    }

    return false;
}

bool DirectiveStack::hasUnfinishedIfOrIfN() const noexcept
{
    SharedPtr<DirectiveList> previous = previousIfOrIfNOrElseIfOrElseOrRegion();
    return previous != nullptr && previous->any() && previous->head() != nullptr && previous->head()->syntaxKind() != SyntaxKind::RegionDirectiveTrivia;
}

bool DirectiveStack::hasPreviousIfOrIfNOrElseIf() const noexcept
{
    SharedPtr<DirectiveList> previous = previousIfOrIfNOrElseIfOrElseOrRegion();

    if (previous != nullptr && previous->any() && previous->head() != nullptr)
    {
        const SyntaxKind headSyntaxKind = previous->head()->syntaxKind();

        switch (headSyntaxKind)
        {
            case SyntaxKind::IfDirectiveTrivia:
            case SyntaxKind::IfDefDirectiveTrivia:
            case SyntaxKind::IfNDefDirectiveTrivia:
            case SyntaxKind::ElseIfDirectiveTrivia:
                return true;
            default:
                return false;
        }
    }

    return false;
}

bool DirectiveStack::hasUnfinishedRegion() const noexcept
{
    SharedPtr<DirectiveList> previous = previousIfOrIfNOrElseIfOrElseOrRegion();
    return previous != nullptr && previous->any() && previous->head() != nullptr && previous->head()->syntaxKind() == SyntaxKind::RegionDirectiveTrivia;
}

DefineState DirectiveStack::isDefined(std::string_view id) const noexcept
{
    for (SharedPtr<DirectiveList> current = _directives; current != nullptr && current->any() && current->head() != nullptr; current = current->tail())
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
                SyntaxKind currentSyntaxKind = SyntaxKind::None;

                do
                {
                    current = current->tail();
                    currentSyntaxKind = current->head()->syntaxKind();

                    if (current == nullptr || !current->any())
                        return DefineState::Unspecified;
                }
                while (currentSyntaxKind != SyntaxKind::IfDirectiveTrivia && currentSyntaxKind != SyntaxKind::IfDefDirectiveTrivia
                       && currentSyntaxKind != SyntaxKind::IfNDefDirectiveTrivia);

                break;
            }
        }
    }

    return DefineState::Unspecified;
}

SharedPtr<DirectiveList> DirectiveStack::previousIfOrIfN() const noexcept
{
    SharedPtr<DirectiveList> current = _directives;

    while (current != nullptr && current->any() && current->head() != nullptr)
    {
        switch (current->head()->syntaxKind())
        {
            case SyntaxKind::IfDirectiveTrivia:
            case SyntaxKind::IfDefDirectiveTrivia:
            case SyntaxKind::IfNDefDirectiveTrivia:
                return current;
        }

        current = current->tail();
    }

    return current;
}

SharedPtr<DirectiveList> DirectiveStack::previousIfOrIfNOrElseIfOrElseOrRegion() const noexcept
{
    SharedPtr<DirectiveList> current = _directives;

    while (current != nullptr && current->any() && current->head() != nullptr)
    {
        switch (current->head()->syntaxKind())
        {
            case SyntaxKind::IfDirectiveTrivia:
            case SyntaxKind::IfDefDirectiveTrivia:
            case SyntaxKind::IfNDefDirectiveTrivia:
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

    while (current != nullptr && current->any() && current->head() != nullptr && current->head()->syntaxKind() != SyntaxKind::RegionDirectiveTrivia)
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

    if (stack->head() != nullptr)
    {
        const SyntaxKind headSyntaxKind = stack->head()->syntaxKind();

        switch (headSyntaxKind)
        {
            case SyntaxKind::IfDirectiveTrivia:
            case SyntaxKind::IfDefDirectiveTrivia:
            case SyntaxKind::IfNDefDirectiveTrivia:
                include = stack->head()->isBranchTaken();
                return stack->tail();
        }
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

} // end namespace polyglot::Core::Parser
