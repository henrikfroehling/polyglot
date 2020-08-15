#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiCompilationUnitSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCompilationUnitSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiCompilationUnitSyntax() noexcept = default;
    inline virtual bool isUnitModule() const noexcept { return false; }
    inline virtual bool isPackageModule() const noexcept { return false; }
    inline virtual bool isProgramModule() const noexcept { return false; }
    inline const SyntaxTokenPtr& EOFToken() const noexcept { return _ptrEOFToken; }
    inline void setEOFToken(SyntaxTokenPtr eofToken) noexcept { _ptrEOFToken = eofToken; }

private:
    std::shared_ptr<SyntaxToken> _ptrEOFToken;
};

using DelphiCompilationUnitSyntaxPtr = std::shared_ptr<DelphiCompilationUnitSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHICOMPILATIONUNITSYNTAX_H
