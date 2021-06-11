#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIGOTOSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIGOTOSTATEMENTSYNTAX_H

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

class DelphiGotoStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiGotoStatementSyntax(Core::Syntax::ISyntaxToken* gotoKeyword,
                                       Core::Syntax::ISyntaxToken* labelToken) noexcept;

    virtual ~DelphiGotoStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* gotoKeyword() const noexcept { return _pGotoKeyword; }
    inline Core::Syntax::ISyntaxToken* labelToken() const noexcept { return _pLabelToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pGotoKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pLabelToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiGotoStatementSyntax"; }

    inline bool isGotoStatement() const noexcept override final { return true; }

    static DelphiGotoStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* gotoKeyword,
                                             Core::Syntax::ISyntaxToken* labelToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pGotoKeyword;
    Core::Syntax::ISyntaxToken* _pLabelToken; // identifier | int num literal | hex num literal
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIGOTOSTATEMENTSYNTAX_H
