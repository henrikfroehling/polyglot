#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitFinalizationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitFinalizationSectionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiUnitFinalizationSectionSyntax() noexcept = default;
};

using DelphiUnitFinalizationSectionSyntaxPtr = std::shared_ptr<DelphiUnitFinalizationSectionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITFINALIZATIONSECTIONSYNTAX_H
