#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
};

using DelphiUnitInterfaceSectionSyntaxPtr = std::shared_ptr<DelphiUnitInterfaceSectionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
