#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class NameExpressionSyntax;

class DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName) noexcept;
    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline NameExpressionSyntax* unitName() const noexcept { return _pUnitName; }
    inline LanguageSyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline void setInKeyword(LanguageSyntaxToken* inKeyword) noexcept { _pInKeyword = inKeyword; }
    inline LanguageSyntaxToken* sourceFile() const noexcept { return _pSourceFile; }
    inline void setSourceFile(LanguageSyntaxToken* sourceFile) noexcept { _pSourceFile = sourceFile; }
    inline LanguageSyntaxToken* commaToken() const noexcept { return _pCommaToken; }
    inline void setCommaToken(LanguageSyntaxToken* commaToken) noexcept { _pCommaToken = commaToken; }

private:
    NameExpressionSyntax* _pUnitName;
    LanguageSyntaxToken* _pInKeyword; // optional
    LanguageSyntaxToken* _pSourceFile; // optional
    LanguageSyntaxToken* _pCommaToken; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
