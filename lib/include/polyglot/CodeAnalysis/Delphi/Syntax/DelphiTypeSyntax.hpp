#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHITYPESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHITYPESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiTypeSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiTypeSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiTypeSyntax() noexcept = default;
};

using DelphiTypeSyntaxPtr = std::shared_ptr<DelphiTypeSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHITYPESYNTAX_H
