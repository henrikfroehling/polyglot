#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API StructuredTriviaSyntax : public SyntaxTrivia
{
public:
    explicit StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~StructuredTriviaSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
