#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(SharedPtr<NameExpressionSyntax> unitName) noexcept;
    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline const SharedPtr<NameExpressionSyntax>& unitName() const noexcept { return _ptrUnitName; }
    inline const SharedPtr<SyntaxToken>& inKeyword() const noexcept { return _ptrInKeyword; }
    inline void setInKeyword(SharedPtr<SyntaxToken> inKeyword) noexcept { _ptrInKeyword = std::move(inKeyword); }
    inline const SharedPtr<SyntaxToken>& sourceFile() const noexcept { return _ptrSourceFile; }
    inline void setSourceFile(SharedPtr<SyntaxToken> sourceFile) noexcept { _ptrSourceFile = std::move(sourceFile); }
    inline const SharedPtr<SyntaxToken>& commaToken() const noexcept { return _ptrCommaToken; }
    inline void setCommaToken(SharedPtr<SyntaxToken> commaToken) noexcept { _ptrCommaToken = std::move(commaToken); }

private:
    SharedPtr<NameExpressionSyntax> _ptrUnitName;
    SharedPtr<SyntaxToken> _ptrInKeyword; // optional
    SharedPtr<SyntaxToken> _ptrSourceFile; // optional
    SharedPtr<SyntaxToken> _ptrCommaToken; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
