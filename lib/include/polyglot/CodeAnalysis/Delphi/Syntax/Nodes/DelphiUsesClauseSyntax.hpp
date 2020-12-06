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
    explicit DelphiUsesClauseSyntax(Ptr<SyntaxToken> usesKeyword,
                                    std::vector<Ptr<DelphiUnitReferenceDeclarationSyntax>> unitReferences,
                                    Ptr<SyntaxToken> semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline const Ptr<SyntaxToken> usesKeyword() const noexcept { return _ptrUsesKeyword; }
    inline const std::vector<Ptr<DelphiUnitReferenceDeclarationSyntax>>& unitReferences() const noexcept { return _unitReferences; }

    inline void addUnitReference(Ptr<DelphiUnitReferenceDeclarationSyntax> unitReference) noexcept
    {
        _unitReferences.push_back(unitReference);
    }

    inline const Ptr<SyntaxToken>& semiColonToken() const noexcept { return _ptrSemiColonToken; }

private:
    Ptr<SyntaxToken> _ptrUsesKeyword;
    std::vector<Ptr<DelphiUnitReferenceDeclarationSyntax>> _unitReferences;
    Ptr<SyntaxToken> _ptrSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
