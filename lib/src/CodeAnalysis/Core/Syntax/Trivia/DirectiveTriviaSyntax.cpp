#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Directive.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveTriviaSyntax::DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : StructuredTriviaSyntax{syntaxKind}
{}

DirectiveStack DirectiveTriviaSyntax::applyDirectives(DirectiveStack stack) const noexcept
{
    return stack.add(std::make_shared<Directive>(const_cast<DirectiveTriviaSyntax*>(this)));
}

} // end namespace polyglot::CodeAnalysis
