#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_STRUCTUREDTRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_STRUCTUREDTRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API StructuredTriviaSyntax : public SyntaxNode
{
public:
    explicit StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~StructuredTriviaSyntax() noexcept = default;
};

using StructuredTriviaSyntaxPtr = std::shared_ptr<StructuredTriviaSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_STRUCTUREDTRIVIASYNTAX_H
