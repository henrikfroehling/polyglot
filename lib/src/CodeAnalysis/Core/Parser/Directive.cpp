#include "CodeAnalysis/Core/Parser/Directive.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

Directive::Directive(DirectiveTriviaSyntax* node) noexcept
    : _pNode{node}
{}

bool Directive::isBranchTaken() const noexcept
{
    BranchingDirectiveTriviaSyntax* ptrBranching = static_cast<BranchingDirectiveTriviaSyntax*>(_pNode);

    if (ptrBranching != nullptr)
        return ptrBranching->isBranchTaken();

    return false;
}

std::string_view Directive::identifier() const noexcept
{
    switch (static_cast<SyntaxNode*>(_pNode)->syntaxKind())
    {
        case SyntaxKind::DefineDirectiveTrivia:
            return static_cast<DefineDirectiveTriviaSyntax*>(_pNode)->name()->text();
        case SyntaxKind::UndefDirectiveTrivia:
            return static_cast<UndefDirectiveTriviaSyntax*>(_pNode)->name()->text();
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
