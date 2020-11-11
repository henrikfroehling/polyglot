#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Tokens/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSimpleNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiSimpleNameSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSimpleNameSyntax() noexcept = default;
    virtual const SyntaxTokenPtr& identifier() const noexcept = 0;
};

using DelphiSimpleNameSyntaxPtr = std::shared_ptr<DelphiSimpleNameSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
