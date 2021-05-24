#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICOMPOUNDSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICOMPOUNDSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

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
    explicit DelphiCompoundStatementSyntax(Core::Syntax::ISyntaxToken* beginToken,
                                           DelphiStatementListSyntax* statementList,
                                           Core::Syntax::ISyntaxToken* endToken) noexcept;

    virtual ~DelphiCompoundStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* beginToken() const noexcept { return _pBeginToken; }
    inline DelphiStatementListSyntax* statementList() const noexcept { return _pStatementList; }
    inline Core::Syntax::ISyntaxToken* endToken() const noexcept { return _pEndToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pBeginToken); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pEndToken); }

    inline pg_string typeName() const noexcept override final { return L"DelphiCompoundStatementSyntax"; }

    inline bool isCompoundStatement() const noexcept override final { return true; }

    static DelphiCompoundStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::ISyntaxToken* beginToken,
                                                 DelphiStatementListSyntax* statementList,
                                                 Core::Syntax::ISyntaxToken* endToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pBeginToken;
    DelphiStatementListSyntax* _pStatementList;
    Core::Syntax::ISyntaxToken* _pEndToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICOMPOUNDSTATEMENTSYNTAX_H
