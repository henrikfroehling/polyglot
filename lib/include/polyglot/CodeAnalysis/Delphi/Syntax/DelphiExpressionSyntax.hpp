#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiExpressionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiExpressionSyntax() noexcept = default;
};

using DelphiExpressionSyntaxPtr = std::shared_ptr<DelphiExpressionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H
