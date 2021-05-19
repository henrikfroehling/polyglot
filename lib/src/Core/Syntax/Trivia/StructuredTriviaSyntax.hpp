#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;

class StructuredTriviaSyntax : public SyntaxTrivia
{
public:
    explicit StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~StructuredTriviaSyntax() noexcept {}
    inline bool isStructuredTrivia() const noexcept override final { return true; }

    inline virtual pg_size childCount() const noexcept { return 0; }
    inline virtual SyntaxVariant child(pg_size index) const { return SyntaxVariant::empty(); }

    virtual std::string typeName() const noexcept override { return "StructuredTriviaSyntax"; }

protected:
    void adjustWidth(ISyntaxNode* node) noexcept;
    void adjustWidth(ISyntaxToken* token) noexcept;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_STRUCTUREDTRIVIASYNTAX_H
