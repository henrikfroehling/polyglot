#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_NAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_NAMEEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/TypeExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API NameExpressionSyntax : public TypeExpressionSyntax
{
public:
    explicit NameExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~NameExpressionSyntax() noexcept = default;
};

using NameExpressionSyntaxPtr = std::shared_ptr<NameExpressionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_NAMEEXPRESSIONSYNTAX_H
