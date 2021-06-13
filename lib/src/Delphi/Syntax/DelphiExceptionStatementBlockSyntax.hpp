#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONSTATEMENTBLOCKSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONSTATEMENTBLOCKSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptionBlockSyntax.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExceptionStatementBlockSyntax : public DelphiExceptionBlockSyntax
{
public:
    explicit DelphiExceptionStatementBlockSyntax(DelphiStatementListSyntax* statements) noexcept;
    virtual ~DelphiExceptionStatementBlockSyntax() noexcept {}

    inline DelphiStatementListSyntax* statements() const noexcept { return _pStatements; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pStatements); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pStatements); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExceptionStatementBlockSyntax"; }
    inline bool isStatementList() const noexcept override final { return true; }

    static DelphiExceptionStatementBlockSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                       DelphiStatementListSyntax* statements) noexcept;

private:
    DelphiStatementListSyntax* _pStatements;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONSTATEMENTBLOCKSYNTAX_H
