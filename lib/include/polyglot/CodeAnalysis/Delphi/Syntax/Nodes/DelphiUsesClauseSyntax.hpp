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
    explicit DelphiUsesClauseSyntax(SyntaxToken* usesKeyword,
                                    std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences,
                                    SyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline SyntaxToken* usesKeyword() const noexcept { return _ptrUsesKeyword; }
    inline const std::vector<DelphiUnitReferenceDeclarationSyntax*>& unitReferences() const noexcept { return _unitReferences; }

    inline void addUnitReference(DelphiUnitReferenceDeclarationSyntax* unitReference) noexcept
    {
        _unitReferences.push_back(unitReference);
    }

    inline SyntaxToken* semiColonToken() const noexcept { return _ptrSemiColonToken; }

private:
    SyntaxToken* _ptrUsesKeyword;
    std::vector<DelphiUnitReferenceDeclarationSyntax*> _unitReferences;
    SyntaxToken* _ptrSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
