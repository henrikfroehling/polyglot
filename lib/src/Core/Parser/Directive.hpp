#ifndef POLYGLOT_CORE_PARSER_DIRECTIVE_H
#define POLYGLOT_CORE_PARSER_DIRECTIVE_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"
#include "Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::Core::Parser
{

class Directive
{
public:
    explicit Directive(Syntax::DirectiveTriviaSyntax* trivia) noexcept;
    virtual ~Directive() noexcept {}
    inline Syntax::SyntaxKind syntaxKind() const noexcept { return _pTrivia != nullptr ? static_cast<Syntax::SyntaxTrivia*>(_pTrivia)->syntaxKind() : Syntax::SyntaxKind::None; }
    inline bool isActive() const noexcept { return _pTrivia != nullptr ? _pTrivia->isActive() : false; }
    bool isBranchTaken() const noexcept;
    pg_string_view identifier() const noexcept;

    friend bool operator==(const Directive& lhs,
                           const Directive& rhs) noexcept;

    friend bool operator!=(const Directive& lhs,
                           const Directive& rhs) noexcept;

private:
    Syntax::DirectiveTriviaSyntax* _pTrivia;
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_DIRECTIVE_H
