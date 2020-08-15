#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
};

using DelphiUnitImplementationSectionSyntaxPtr = std::shared_ptr<DelphiUnitImplementationSectionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
