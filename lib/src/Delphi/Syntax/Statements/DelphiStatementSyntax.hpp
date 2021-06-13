#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHISTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHISTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiStatementSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiStatementSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiStatementSyntax() noexcept {}

    inline bool isStatement() const noexcept override final { return true; }
    inline virtual pg_string typeName() const noexcept override { return L"DelphiStatementSyntax"; }

    inline virtual bool isExpressionStatement() const noexcept { return false; }
    inline virtual bool isIfStatement() const noexcept { return false; }
    inline virtual bool isCaseStatement() const noexcept { return false; }
    inline virtual bool isRepeatStatement() const noexcept { return false; }
    inline virtual bool isWhileStatement() const noexcept { return false; }
    inline virtual bool isForStatement() const noexcept { return false; }
    inline virtual bool isWithStatement() const noexcept { return false; }
    inline virtual bool isTryStatement() const noexcept { return false; }
    inline virtual bool isRaiseStatement() const noexcept { return false; }
    inline virtual bool isAssemblerStatement() const noexcept { return false; }
    inline virtual bool isCompoundStatement() const noexcept { return false; }
    inline virtual bool isBreakStatement() const noexcept { return false; }
    inline virtual bool isContinueStatement() const noexcept { return false; }
    inline virtual bool isExitStatement() const noexcept { return false; }
    inline virtual bool isGotoStatement() const noexcept { return false; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHISTATEMENTSYNTAX_H
