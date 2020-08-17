#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitHeadingSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadingSyntax(SyntaxTokenPtr unitKeyword,
                                     DelphiNameSyntaxPtr name) noexcept;

    virtual ~DelphiUnitHeadingSyntax() noexcept = default;
    const SyntaxTokenPtr& unitKeyword() const noexcept { return _ptrUnitKeyword; }
    const DelphiNameSyntaxPtr& name() const noexcept { return _ptrName; }

private:
    SyntaxTokenPtr _ptrUnitKeyword;
    DelphiNameSyntaxPtr _ptrName;
};

using DelphiUnitHeadingSyntaxPtr = std::shared_ptr<DelphiUnitHeadingSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H
