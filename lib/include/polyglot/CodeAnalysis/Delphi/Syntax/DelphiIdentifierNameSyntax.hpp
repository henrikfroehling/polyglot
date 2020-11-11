#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Tokens/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiIdentifierNameSyntax : public DelphiSimpleNameSyntax
{
public:
    explicit DelphiIdentifierNameSyntax(SyntaxTokenPtr identifier) noexcept;
    virtual ~DelphiIdentifierNameSyntax() noexcept = default;
    virtual const SyntaxTokenPtr& identifier() const noexcept override { return _ptrIdentifier; }

protected:
    SyntaxTokenPtr _ptrIdentifier;
};

using DelphiIdentifierNameSyntaxPtr = std::shared_ptr<DelphiIdentifierNameSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIIDENTIFIERNAMESYNTAX_H
