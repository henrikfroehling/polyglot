#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHITRYSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHITRYSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiStatementListSyntax;

class DelphiTryStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiTryStatementSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                      Core::Syntax::ISyntaxToken* tryKeyword,
                                      DelphiStatementListSyntax* statements,
                                      Core::Syntax::ISyntaxToken* endKeyword,
                                      Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiTryStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* tryKeyword() const noexcept { return _pTryKeyword; }
    inline DelphiStatementListSyntax* statements() const noexcept { return _pStatements; }
    inline Core::Syntax::ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pTryKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiTryStatementSyntax"; }

    inline bool isTryStatement() const noexcept override final { return true; }
    inline virtual bool isTryExceptStatement() const noexcept { return false; }
    inline virtual bool isTryFinallyStatement() const noexcept { return false; }

protected:
    Core::Syntax::ISyntaxToken* _pTryKeyword;
    DelphiStatementListSyntax* _pStatements;
    Core::Syntax::ISyntaxToken* _pEndKeyword;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHITRYSTATEMENTSYNTAX_H
