#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

class SimpleNameExpressionSyntax : public NameExpressionSyntax
{
public:
    explicit SimpleNameExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~SimpleNameExpressionSyntax() noexcept {}
    virtual ISyntaxToken* identifier() const noexcept = 0;

    inline virtual pg_string typeName() const noexcept override { return L"SimpleNameExpressionSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_SIMPLENAMEEXPRESSIONSYNTAX_H
