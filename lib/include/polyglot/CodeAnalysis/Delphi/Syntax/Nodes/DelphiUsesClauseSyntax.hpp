#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUsesClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUsesClauseSyntax(SharedPtr<SyntaxToken> usesKeyword,
                                    std::vector<SharedPtr<DelphiUnitReferenceDeclarationSyntax>> unitReferences,
                                    SharedPtr<SyntaxToken> semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline const SharedPtr<SyntaxToken>& usesKeyword() const noexcept { return _ptrUsesKeyword; }
    inline const std::vector<SharedPtr<DelphiUnitReferenceDeclarationSyntax>>& unitReferences() const noexcept { return _unitReferences; }

    inline void addUnitReference(SharedPtr<DelphiUnitReferenceDeclarationSyntax> unitReference) noexcept
    {
        _unitReferences.push_back(std::move(unitReference));
    }

    inline const SharedPtr<SyntaxToken>& semiColonToken() const noexcept { return _ptrSemiColonToken; }

private:
    SharedPtr<SyntaxToken> _ptrUsesKeyword;
    std::vector<SharedPtr<DelphiUnitReferenceDeclarationSyntax>> _unitReferences;
    SharedPtr<SyntaxToken> _ptrSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
