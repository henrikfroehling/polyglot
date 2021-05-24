#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class UndefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~UndefDirectiveTriviaSyntax() noexcept {}
    inline virtual pg_string_view definitionName() const noexcept = 0;

    inline virtual pg_string typeName() const noexcept override { return L"UndefDirectiveTriviaSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
