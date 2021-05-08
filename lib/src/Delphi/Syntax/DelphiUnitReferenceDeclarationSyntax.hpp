#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "DelphiSyntaxList.hpp"

namespace polyglot::Delphi::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class NameExpressionSyntax;
class SyntaxFactory;

class DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName,
                                                  ISyntaxToken* inKeyword = nullptr,
                                                  ISyntaxToken* sourceFile = nullptr) noexcept;

    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline NameExpressionSyntax* unitName() const noexcept { return _pUnitName; }
    inline ISyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline ISyntaxToken* sourceFile() const noexcept { return _pSourceFile; }
    inline pg_size childCount() const noexcept override { return _pSourceFile != nullptr ? 3 : 1; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiUnitReferenceDeclarationSyntax* create(SyntaxFactory& syntaxFactory,
                                                        NameExpressionSyntax* unitName,
                                                        ISyntaxToken* inKeyword = nullptr,
                                                        ISyntaxToken* sourceFile = nullptr) noexcept;

private:
    NameExpressionSyntax* _pUnitName;
    ISyntaxToken* _pInKeyword; // optional
    ISyntaxToken* _pSourceFile; // optional, but needs _pInKeyword
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
