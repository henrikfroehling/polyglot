#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSimpleNameSyntax : public DelphiNameSyntax
{
public:
    virtual ~DelphiSimpleNameSyntax() noexcept = default;
    inline SyntaxToken* identifier() const noexcept { return _ptrIdentifier.get(); }

protected:
    explicit DelphiSimpleNameSyntax(SyntaxKind syntaxKind,
                                    std::shared_ptr<SyntaxToken> identifier) noexcept;

protected:
    std::shared_ptr<SyntaxToken> _ptrIdentifier;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
