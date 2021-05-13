#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H

#include <string_view>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DefineDirectiveTriviaSyntax() noexcept {}
    inline virtual std::string_view definitionName() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
