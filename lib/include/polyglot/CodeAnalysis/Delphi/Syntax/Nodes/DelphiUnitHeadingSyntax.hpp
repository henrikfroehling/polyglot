#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitHeadingSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadingSyntax(SyntaxTokenPtr unitKeyword,
                                     NameExpressionSyntaxPtr name,
                                     SyntaxTokenPtr semiColonToken) noexcept;

    virtual ~DelphiUnitHeadingSyntax() noexcept = default;
    const SyntaxTokenPtr& unitKeyword() const noexcept { return _ptrUnitKeyword; }
    const NameExpressionSyntaxPtr& name() const noexcept { return _ptrName; }
    const SyntaxTokenPtr& semiColonToken() const noexcept { return _ptrSemiColonToken; }

private:
    SyntaxTokenPtr _ptrUnitKeyword;
    NameExpressionSyntaxPtr _ptrName;
    SyntaxTokenPtr _ptrSemiColonToken;
};

using DelphiUnitHeadingSyntaxPtr = std::shared_ptr<DelphiUnitHeadingSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H
