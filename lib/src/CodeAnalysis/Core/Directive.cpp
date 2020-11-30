#include "polyglot/CodeAnalysis/Core/Directive.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

Directive::Directive(SharedPtr<DirectiveTriviaSyntax> node) noexcept
    : _node{std::move(node)}
{}

bool Directive::isBranchTaken() const noexcept
{
    SharedPtr<BranchingDirectiveTriviaSyntax> ptrBranching = std::dynamic_pointer_cast<BranchingDirectiveTriviaSyntax>(_node);

    if (ptrBranching != nullptr)
        return ptrBranching->isBranchTaken();

    return false;
}

std::string_view Directive::identifier() const noexcept
{
    switch (_node->syntaxKind())
    {
        case SyntaxKind::DefineDirectiveTrivia:
            return std::dynamic_pointer_cast<DefineDirectiveTriviaSyntax>(_node)->name()->text();
        case SyntaxKind::UndefDirectiveTrivia:
            return std::dynamic_pointer_cast<UndefDirectiveTriviaSyntax>(_node)->name()->text();
        default:
            return std::string_view{};
    }
}

bool operator==(const Directive& lhs,
                const Directive& rhs) noexcept
{
    return lhs.identifier() == rhs.identifier();
}

bool operator!=(const Directive& lhs,
                const Directive& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::CodeAnalysis
