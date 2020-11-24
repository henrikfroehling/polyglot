#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IDENTIFIERNAMEEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class IdentifierNameExpressionSyntax;
using IdentifierNameExpressionSyntaxPtr = std::shared_ptr<IdentifierNameExpressionSyntax>;

class POLYGLOT_API IdentifierNameExpressionSyntax : public SimpleNameExpressionSyntax
{
public:
    explicit IdentifierNameExpressionSyntax(SyntaxTokenPtr identifier) noexcept;
    virtual ~IdentifierNameExpressionSyntax() noexcept = default;
    virtual const SyntaxTokenPtr& identifier() const noexcept override { return _ptrIdentifier; }

    static IdentifierNameExpressionSyntaxPtr create(SyntaxTokenPtr identifier) noexcept;

protected:
    SyntaxTokenPtr _ptrIdentifier;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
