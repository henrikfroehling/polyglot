#include "DirectiveTriviaSyntax.hpp"
#include "Core/Parser/Directive.hpp"

namespace polyglot::Core::Syntax
{

DirectiveTriviaSyntax::DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : StructuredTriviaSyntax{syntaxKind}
{}

DirectiveStack DirectiveTriviaSyntax::applyDirectives(DirectiveStack stack) const noexcept
{
    return stack.add(std::make_shared<Directive>(const_cast<DirectiveTriviaSyntax*>(this)));
}

} // end namespace polyglot::Core::Syntax
