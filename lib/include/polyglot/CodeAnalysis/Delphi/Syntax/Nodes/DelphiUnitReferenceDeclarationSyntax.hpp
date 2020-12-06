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
    explicit DelphiUnitReferenceDeclarationSyntax(Ptr<NameExpressionSyntax> unitName) noexcept;
    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline const Ptr<NameExpressionSyntax> unitName() const noexcept { return _ptrUnitName; }
    inline const Ptr<SyntaxToken> inKeyword() const noexcept { return _ptrInKeyword; }
    inline void setInKeyword(Ptr<SyntaxToken> inKeyword) noexcept { _ptrInKeyword = inKeyword; }
    inline const Ptr<SyntaxToken> sourceFile() const noexcept { return _ptrSourceFile; }
    inline void setSourceFile(Ptr<SyntaxToken> sourceFile) noexcept { _ptrSourceFile = sourceFile; }
    inline const Ptr<SyntaxToken> commaToken() const noexcept { return _ptrCommaToken; }
    inline void setCommaToken(Ptr<SyntaxToken> commaToken) noexcept { _ptrCommaToken = commaToken; }

private:
    Ptr<NameExpressionSyntax> _ptrUnitName;
    Ptr<SyntaxToken> _ptrInKeyword; // optional
    Ptr<SyntaxToken> _ptrSourceFile; // optional
    Ptr<SyntaxToken> _ptrCommaToken; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
