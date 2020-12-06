#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DirectiveTriviaSyntax : public StructuredTriviaSyntax
{
public:
    explicit DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DirectiveTriviaSyntax() noexcept = default;
    virtual const Ptr<SyntaxToken> startToken() const noexcept = 0;
    virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept = 0;
    virtual bool isActive() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DIRECTIVETRIVIASYNTAX_H
