#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class StructuredTriviaSyntax : public SyntaxTrivia
{
public:
    explicit StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~StructuredTriviaSyntax() noexcept = default;
    inline bool isStructuredTrivia() const noexcept override { return true; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
