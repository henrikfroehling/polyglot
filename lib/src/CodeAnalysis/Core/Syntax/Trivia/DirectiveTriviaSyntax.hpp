#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Parser/DirectiveStack.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class DirectiveTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DirectiveTriviaSyntax() noexcept = default;
    virtual LanguageSyntaxToken* startToken() const noexcept = 0;
    virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept = 0;
    virtual bool isActive() const noexcept = 0;
    virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept override;
    inline bool isDirective() const noexcept override { return true; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DIRECTIVETRIVIASYNTAX_H
