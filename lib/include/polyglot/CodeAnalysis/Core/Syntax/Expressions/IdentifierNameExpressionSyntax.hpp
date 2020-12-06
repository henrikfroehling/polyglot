#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IDENTIFIERNAMEEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API IdentifierNameExpressionSyntax : public SimpleNameExpressionSyntax
{
public:
    explicit IdentifierNameExpressionSyntax(Ptr<SyntaxToken> identifier) noexcept;
    virtual ~IdentifierNameExpressionSyntax() noexcept = default;
    virtual const Ptr<SyntaxToken> identifier() const noexcept override { return _ptrIdentifier; }

    static Ptr<IdentifierNameExpressionSyntax> create(Ptr<SyntaxToken> identifier) noexcept;

protected:
    Ptr<SyntaxToken> _ptrIdentifier;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IDENTIFIERNAMEEXPRESSIONSYNTAX_H
