#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include <memory>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Tokens/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUsesClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUsesClauseSyntax(SyntaxTokenPtr usesKeyword,
                                    std::vector<DelphiUnitReferenceDeclarationSyntaxPtr> unitReferences,
                                    SyntaxTokenPtr semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline const SyntaxTokenPtr& usesKeyword() const noexcept { return _ptrUsesKeyword; }
    inline const std::vector<DelphiUnitReferenceDeclarationSyntaxPtr>& unitReferences() const noexcept { return _unitReferences; }

    inline void addUnitReference(DelphiUnitReferenceDeclarationSyntaxPtr unitReference) noexcept
    {
        _unitReferences.push_back(std::move(unitReference));
    }

    inline const SyntaxTokenPtr& semiColonToken() const noexcept { return _ptrSemiColonToken; }

private:
    SyntaxTokenPtr _ptrUsesKeyword;
    std::vector<DelphiUnitReferenceDeclarationSyntaxPtr> _unitReferences;
    SyntaxTokenPtr _ptrSemiColonToken;
};

using DelphiUsesClauseSyntaxPtr = std::shared_ptr<DelphiUsesClauseSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
