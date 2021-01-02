#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Directive.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveTriviaSyntax::DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : StructuredTriviaSyntax{syntaxKind}
{
    _flags |= SyntaxNodeFlags::ContainsDirectives;
}

DirectiveStack DirectiveTriviaSyntax::applyDirectives(DirectiveStack stack) const noexcept
{
    return stack.add(std::make_shared<Directive>(const_cast<DirectiveTriviaSyntax*>(this)));
}

} // end namespace polyglot::CodeAnalysis
