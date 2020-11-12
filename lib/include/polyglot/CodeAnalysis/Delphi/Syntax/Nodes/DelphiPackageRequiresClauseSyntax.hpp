#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiPackageRequiresClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageRequiresClauseSyntax() noexcept;
    virtual ~DelphiPackageRequiresClauseSyntax() noexcept = default;
};

using DelphiPackageRequiresClauseSyntaxPtr = std::shared_ptr<DelphiPackageRequiresClauseSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEREQUIRESCLAUSESYNTAX_H
