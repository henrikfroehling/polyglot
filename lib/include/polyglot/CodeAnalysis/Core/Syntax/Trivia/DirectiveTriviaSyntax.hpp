#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
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
    virtual const SyntaxTokenPtr& startToken() const noexcept = 0;
    virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept = 0;
    virtual bool isActive() const noexcept = 0;
};

using DirectiveTriviaSyntaxPtr = std::shared_ptr<DirectiveTriviaSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DIRECTIVETRIVIASYNTAX_H
