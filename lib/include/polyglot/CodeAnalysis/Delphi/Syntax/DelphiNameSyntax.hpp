#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHINAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHINAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiTypeSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiNameSyntax : public DelphiTypeSyntax
{
public:
    explicit DelphiNameSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiNameSyntax() noexcept = default;
};

using DelphiNameSyntaxPtr = std::shared_ptr<DelphiNameSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHINAMESYNTAX_H
