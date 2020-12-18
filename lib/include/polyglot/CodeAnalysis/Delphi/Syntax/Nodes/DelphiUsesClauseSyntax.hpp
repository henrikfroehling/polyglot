#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUSESCLAUSESYNTAX_H

#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API DelphiUsesClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUsesClauseSyntax(SyntaxToken* usesKeyword,
                                    std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences,
                                    SyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline SyntaxToken* usesKeyword() const noexcept { return _pUsesKeyword; }
    inline const std::vector<DelphiUnitReferenceDeclarationSyntax*>& unitReferences() const noexcept { return _unitReferences; }

    inline void addUnitReference(DelphiUnitReferenceDeclarationSyntax* unitReference) noexcept
    {
        _unitReferences.push_back(unitReference);
    }

    inline SyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

private:
    SyntaxToken* _pUsesKeyword;
    std::vector<DelphiUnitReferenceDeclarationSyntax*> _unitReferences;
    SyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUSESCLAUSESYNTAX_H
