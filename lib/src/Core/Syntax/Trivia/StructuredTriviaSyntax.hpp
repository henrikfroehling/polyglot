#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::Core::Syntax
{

class StructuredTriviaSyntax : public SyntaxTrivia
{
public:
    explicit StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~StructuredTriviaSyntax() noexcept = default;
    inline bool isStructuredTrivia() const noexcept override { return true; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
