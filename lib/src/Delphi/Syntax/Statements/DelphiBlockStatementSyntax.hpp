#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIBLOCKSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIBLOCKSTATEMENTSYNTAX_H

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

class DelphiBlockStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiBlockStatementSyntax(Core::Syntax::ISyntaxToken* beginKeyword,
                                        DelphiStatementListSyntax* statementList,
                                        Core::Syntax::ISyntaxToken* endKeyword,
                                        Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiBlockStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* beginKeyword() const noexcept { return _pBeginKeyword; }
    inline DelphiStatementListSyntax* statementList() const noexcept { return _pStatementList; }
    inline Core::Syntax::ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pBeginKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline pg_string typeName() const noexcept override final { return L"DelphiBlockStatementSyntax"; }

    inline bool isCompoundStatement() const noexcept override final { return true; }

    static DelphiBlockStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* beginKeyword,
                                              DelphiStatementListSyntax* statementList,
                                              Core::Syntax::ISyntaxToken* endKeyword,
                                              Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pBeginKeyword;
    DelphiStatementListSyntax* _pStatementList;
    Core::Syntax::ISyntaxToken* _pEndKeyword;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIBLOCKSTATEMENTSYNTAX_H
