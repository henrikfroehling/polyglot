#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Parser/DirectiveStack.hpp"
#include "Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

class DirectiveTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DirectiveTriviaSyntax() noexcept {}
    virtual ISyntaxToken* startToken() const noexcept = 0;
    virtual ISyntaxToken* endOfDirectiveToken() const noexcept = 0;
    virtual bool isActive() const noexcept = 0;
    virtual Parser::DirectiveStack applyDirectives(Parser::DirectiveStack stack) const noexcept override;
    inline bool isDirective() const noexcept override final { return true; }

    inline virtual pg_string typeName() const noexcept override { return L"DirectiveTriviaSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H
