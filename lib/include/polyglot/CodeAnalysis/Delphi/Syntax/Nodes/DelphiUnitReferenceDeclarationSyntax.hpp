#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntaxPtr unitName) noexcept;
    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept = default;
    inline const NameExpressionSyntaxPtr& unitName() const noexcept { return _ptrUnitName; }
    inline const SyntaxTokenPtr& inKeyword() const noexcept { return _ptrInKeyword; }
    inline void setInKeyword(SyntaxTokenPtr inKeyword) noexcept { _ptrInKeyword = std::move(inKeyword); }
    inline const SyntaxTokenPtr& sourceFile() const noexcept { return _ptrSourceFile; }
    inline void setSourceFile(SyntaxTokenPtr sourceFile) noexcept { _ptrSourceFile = std::move(sourceFile); }
    inline const SyntaxTokenPtr& commaToken() const noexcept { return _ptrCommaToken; }
    inline void setCommaToken(SyntaxTokenPtr commaToken) noexcept { _ptrCommaToken = std::move(commaToken); }

private:
    NameExpressionSyntaxPtr _ptrUnitName;
    SyntaxTokenPtr _ptrInKeyword; // optional
    SyntaxTokenPtr _ptrSourceFile; // optional
    SyntaxTokenPtr _ptrCommaToken; // optional
};

using DelphiUnitReferenceDeclarationSyntaxPtr = std::shared_ptr<DelphiUnitReferenceDeclarationSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
