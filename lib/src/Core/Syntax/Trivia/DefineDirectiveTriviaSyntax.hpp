#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DefineDirectiveTriviaSyntax() noexcept {}
    inline virtual pg_string_view definitionName() const noexcept = 0;

    inline virtual pg_string typeName() const noexcept override { return L"DefineDirectiveTriviaSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
