#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Nodes/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ExpressionSyntax : public SyntaxNode
{
public:
    explicit ExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ExpressionSyntax() noexcept = default;
};

using ExpressionSyntaxPtr = std::shared_ptr<ExpressionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONSYNTAX_H
