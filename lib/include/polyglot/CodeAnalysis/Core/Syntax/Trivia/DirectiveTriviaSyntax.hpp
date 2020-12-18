#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API DirectiveTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DirectiveTriviaSyntax() noexcept = default;
    virtual SyntaxToken* startToken() const noexcept = 0;
    virtual SyntaxToken* endOfDirectiveToken() const noexcept = 0;
    virtual bool isActive() const noexcept = 0;
    virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept override;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H
