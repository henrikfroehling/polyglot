#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHILABELEDSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHILABELEDSTATEMENTSYNTAX_H

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

class DelphiLabeledStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiLabeledStatementSyntax(Core::Syntax::ISyntaxToken* labelIdentifier,
                                          Core::Syntax::ISyntaxToken* colonToken,
                                          DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiLabeledStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* labelIdentifier() const noexcept { return _pLabelIdentifier; }
    inline Core::Syntax::ISyntaxToken* colonToken() const noexcept { return _pColonToken; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }

    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pLabelIdentifier); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pStatement); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiLabeledStatementSyntax"; }

    static DelphiLabeledStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                Core::Syntax::ISyntaxToken* labelIdentifier,
                                                Core::Syntax::ISyntaxToken* colonToken,
                                                DelphiStatementSyntax* statement) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pLabelIdentifier;
    Core::Syntax::ISyntaxToken* _pColonToken;
    DelphiStatementSyntax* _pStatement;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHILABELEDSTATEMENTSYNTAX_H
