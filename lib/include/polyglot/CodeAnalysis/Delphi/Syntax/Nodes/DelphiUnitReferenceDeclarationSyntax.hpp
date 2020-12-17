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
    inline NameExpressionSyntax* unitName() const noexcept { return _ptrUnitName; }
    inline SyntaxToken* inKeyword() const noexcept { return _ptrInKeyword; }
    inline void setInKeyword(SyntaxToken* inKeyword) noexcept { _ptrInKeyword = inKeyword; }
    inline SyntaxToken* sourceFile() const noexcept { return _ptrSourceFile; }
    inline void setSourceFile(SyntaxToken* sourceFile) noexcept { _ptrSourceFile = sourceFile; }
    inline SyntaxToken* commaToken() const noexcept { return _ptrCommaToken; }
    inline void setCommaToken(SyntaxToken* commaToken) noexcept { _ptrCommaToken = commaToken; }

private:
    NameExpressionSyntax* _ptrUnitName;
    SyntaxToken* _ptrInKeyword; // optional
    SyntaxToken* _ptrSourceFile; // optional
    SyntaxToken* _ptrCommaToken; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
