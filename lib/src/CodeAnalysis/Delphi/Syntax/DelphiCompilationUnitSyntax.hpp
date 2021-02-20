#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;
class SyntaxFactory;

class DelphiCompilationUnitSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCompilationUnitSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* EOFToken) noexcept;

    virtual ~DelphiCompilationUnitSyntax() noexcept = default;
    inline virtual bool isUnitModule() const noexcept { return false; }
    inline virtual bool isPackageModule() const noexcept { return false; }
    inline virtual bool isProgramModule() const noexcept { return false; }
    inline ISyntaxToken* EOFToken() const noexcept { return _pEOFToken; }

    static DelphiCompilationUnitSyntax* create(SyntaxFactory& syntaxFactory,
                                               SyntaxKind syntaxKind,
                                               ISyntaxToken* EOFToken) noexcept;

protected:
    ISyntaxToken* _pEOFToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
