#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIFORSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIFORSTATEMENTSYNTAX_H

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

class DelphiForStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiForStatementSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                      Core::Syntax::ISyntaxToken* forKeyword,
                                      Core::Syntax::ISyntaxToken* doKeyword,
                                      DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiForStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* forKeyword() const noexcept { return _pForKeyword; }
    inline Core::Syntax::ISyntaxToken* doKeyword() const noexcept { return _pDoKeyword; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pForKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pStatement); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiForStatementSyntax"; }

    inline bool isForStatement() const noexcept override final { return true; }
    inline virtual bool isForToStatement() const noexcept { return false; }
    inline virtual bool isForInStatement() const noexcept { return false; }

protected:
    Core::Syntax::ISyntaxToken* _pForKeyword;
    Core::Syntax::ISyntaxToken* _pDoKeyword;
    DelphiStatementSyntax* _pStatement;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIFORSTATEMENTSYNTAX_H
