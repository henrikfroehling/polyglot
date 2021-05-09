#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCompilationUnitSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCompilationUnitSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                         Core::Syntax::ISyntaxToken* EOFToken) noexcept;

    virtual ~DelphiCompilationUnitSyntax() noexcept {}
    inline virtual bool isUnitModule() const noexcept { return false; }
    inline virtual bool isPackageModule() const noexcept { return false; }
    inline virtual bool isProgramModule() const noexcept { return false; }
    inline Core::Syntax::ISyntaxToken* EOFToken() const noexcept { return _pEOFToken; }

    static DelphiCompilationUnitSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                               Core::Syntax::SyntaxKind syntaxKind,
                                               Core::Syntax::ISyntaxToken* EOFToken) noexcept;

protected:
    Core::Syntax::ISyntaxToken* _pEOFToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
