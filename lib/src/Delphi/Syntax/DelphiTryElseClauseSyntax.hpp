#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHITRYELSECLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHITRYELSECLAUSESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiTryElseClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiTryElseClauseSyntax(Core::Syntax::ISyntaxToken* elseKeyword,
                                       DelphiStatementListSyntax* statements) noexcept;

    virtual ~DelphiTryElseClauseSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline DelphiStatementListSyntax* statements() const noexcept { return _pStatements; }

    inline pg_size childCount() const noexcept override final { return 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pElseKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pStatements); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiTryElseClauseSyntax"; }

    static DelphiTryElseClauseSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* elseKeyword,
                                             DelphiStatementListSyntax* statements) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pElseKeyword;
    DelphiStatementListSyntax* _pStatements;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHITRYELSECLAUSESYNTAX_H
