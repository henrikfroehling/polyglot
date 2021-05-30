#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICOMPOUNDSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICOMPOUNDSTATEMENTSYNTAX_H

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

class DelphiCompoundStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiCompoundStatementSyntax(Core::Syntax::ISyntaxToken* beginKeyword,
                                           DelphiStatementListSyntax* statementList,
                                           Core::Syntax::ISyntaxToken* endKeyword) noexcept;

    virtual ~DelphiCompoundStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* beginKeyword() const noexcept { return _pBeginKeyword; }
    inline DelphiStatementListSyntax* statementList() const noexcept { return _pStatementList; }
    inline Core::Syntax::ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pBeginKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pEndKeyword); }

    inline pg_string typeName() const noexcept override final { return L"DelphiCompoundStatementSyntax"; }

    inline bool isCompoundStatement() const noexcept override final { return true; }

    static DelphiCompoundStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::ISyntaxToken* beginKeyword,
                                                 DelphiStatementListSyntax* statementList,
                                                 Core::Syntax::ISyntaxToken* endKeyword) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pBeginKeyword;
    DelphiStatementListSyntax* _pStatementList;
    Core::Syntax::ISyntaxToken* _pEndKeyword;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICOMPOUNDSTATEMENTSYNTAX_H
