#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class NameExpressionSyntax;
class SyntaxToken;

class POLYGLOT_API DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName) noexcept;
    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline NameExpressionSyntax* unitName() const noexcept { return _pUnitName; }
    inline SyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline void setInKeyword(SyntaxToken* inKeyword) noexcept { _pInKeyword = inKeyword; }
    inline SyntaxToken* sourceFile() const noexcept { return _pSourceFile; }
    inline void setSourceFile(SyntaxToken* sourceFile) noexcept { _pSourceFile = sourceFile; }
    inline SyntaxToken* commaToken() const noexcept { return _pCommaToken; }
    inline void setCommaToken(SyntaxToken* commaToken) noexcept { _pCommaToken = commaToken; }

private:
    NameExpressionSyntax* _pUnitName;
    SyntaxToken* _pInKeyword; // optional
    SyntaxToken* _pSourceFile; // optional
    SyntaxToken* _pCommaToken; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
