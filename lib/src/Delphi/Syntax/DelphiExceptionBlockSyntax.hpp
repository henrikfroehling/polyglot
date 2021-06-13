#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONBLOCKSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONBLOCKSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiExceptionBlockSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiExceptionBlockSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiExceptionBlockSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiExceptionBlockSyntax"; }
    inline virtual bool isExceptionHandlerList() const noexcept { return false; }
    inline virtual bool isStatementList() const noexcept { return false; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONBLOCKSYNTAX_H
