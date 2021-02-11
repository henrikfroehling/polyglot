#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class NameExpressionSyntax;
class SyntaxFactory;

class DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName,
                                                  LanguageSyntaxToken* inKeyword = nullptr,
                                                  LanguageSyntaxToken* sourceFile = nullptr) noexcept;

    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline NameExpressionSyntax* unitName() const noexcept { return _pUnitName; }
    inline LanguageSyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline LanguageSyntaxToken* sourceFile() const noexcept { return _pSourceFile; }

    static DelphiUnitReferenceDeclarationSyntax* create(SyntaxFactory& syntaxFactory,
                                                        NameExpressionSyntax* unitName,
                                                        LanguageSyntaxToken* inKeyword = nullptr,
                                                        LanguageSyntaxToken* sourceFile = nullptr) noexcept;

private:
    NameExpressionSyntax* _pUnitName;
    LanguageSyntaxToken* _pInKeyword; // optional
    LanguageSyntaxToken* _pSourceFile; // optional, but needs _pInKeyword
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
