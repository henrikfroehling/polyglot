#include "Directive.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Parser
{

using namespace Core::Syntax;

Directive::Directive(DirectiveTriviaSyntax* trivia) noexcept
    : _pTrivia{trivia}
{}

bool Directive::isBranchTaken() const noexcept
{
    BranchingDirectiveTriviaSyntax* ptrBranching = static_cast<BranchingDirectiveTriviaSyntax*>(_pTrivia);

    if (ptrBranching != nullptr)
        return ptrBranching->isBranchTaken();

    return false;
}

std::string_view Directive::identifier() const noexcept
{
    switch (static_cast<SyntaxTrivia*>(_pTrivia)->syntaxKind())
    {
        case SyntaxKind::DefineDirectiveTrivia:
            return static_cast<DefineDirectiveTriviaSyntax*>(_pTrivia)->name()->text();
        case SyntaxKind::UndefDirectiveTrivia:
            return static_cast<UndefDirectiveTriviaSyntax*>(_pTrivia)->name()->text();
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

} // end namespace polyglot::Core::Parser
