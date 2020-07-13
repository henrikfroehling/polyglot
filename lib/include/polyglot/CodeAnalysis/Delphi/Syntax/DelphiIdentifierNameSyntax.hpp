#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiIdentifierNameSyntax : public DelphiSimpleNameSyntax
{
public:
    virtual ~DelphiIdentifierNameSyntax() noexcept = default;

protected:
    explicit DelphiIdentifierNameSyntax(SyntaxKind syntaxKind,
                                        std::unique_ptr<SyntaxToken> identifier) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H
