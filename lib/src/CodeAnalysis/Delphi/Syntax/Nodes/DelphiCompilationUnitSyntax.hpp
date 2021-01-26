#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHICOMPILATIONUNITSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHICOMPILATIONUNITSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class DelphiCompilationUnitSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCompilationUnitSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiCompilationUnitSyntax() noexcept = default;
    inline virtual bool isUnitModule() const noexcept { return false; }
    inline virtual bool isPackageModule() const noexcept { return false; }
    inline virtual bool isProgramModule() const noexcept { return false; }
    inline LanguageSyntaxToken* EOFToken() const noexcept { return _pEOFToken; }
    inline void setEOFToken(LanguageSyntaxToken* eofToken) noexcept { _pEOFToken = eofToken; }

private:
    LanguageSyntaxToken* _pEOFToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHICOMPILATIONUNITSYNTAX_H
