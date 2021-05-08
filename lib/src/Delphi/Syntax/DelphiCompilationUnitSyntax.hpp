#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
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

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
