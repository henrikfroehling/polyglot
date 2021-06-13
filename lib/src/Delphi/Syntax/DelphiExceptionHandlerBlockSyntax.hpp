#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONHANDLERBLOCKSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONHANDLERBLOCKSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptionBlockSyntax.hpp"
#include "Delphi/Syntax/DelphiTryElseClauseSyntax.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExceptionHandlerBlockSyntax : public DelphiExceptionBlockSyntax
{
public:
    explicit DelphiExceptionHandlerBlockSyntax(DelphiStatementListSyntax* exceptionHandlers,
                                               DelphiTryElseClauseSyntax* elseClause = nullptr) noexcept;

    virtual ~DelphiExceptionHandlerBlockSyntax() noexcept {}

    inline DelphiStatementListSyntax* exceptionHandlers() const noexcept { return _pExceptionHandlers; }
    inline DelphiTryElseClauseSyntax* elseClause() const noexcept { return _pElseClause; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pExceptionHandlers); }

    inline Core::Syntax::SyntaxVariant last() const noexcept override final
    {
        if (_pElseClause != nullptr)
            return Core::Syntax::SyntaxVariant::asNode(_pElseClause);

        return Core::Syntax::SyntaxVariant::asList(_pExceptionHandlers);
    }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExceptionHandlerBlockSyntax"; }
    inline bool isExceptionHandlerList() const noexcept override final { return true; }

    static DelphiExceptionHandlerBlockSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                     DelphiStatementListSyntax* exceptionHandlers,
                                                     DelphiTryElseClauseSyntax* elseClause = nullptr) noexcept;

private:
    DelphiStatementListSyntax* _pExceptionHandlers;
    DelphiTryElseClauseSyntax* _pElseClause; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTIONHANDLERBLOCKSYNTAX_H
