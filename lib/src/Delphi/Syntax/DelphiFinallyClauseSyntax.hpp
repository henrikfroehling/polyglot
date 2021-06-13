#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIFINALLYCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIFINALLYCLAUSESYNTAX_H

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

class DelphiFinallyClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiFinallyClauseSyntax(Core::Syntax::ISyntaxToken* finallyKeyword,
                                       DelphiStatementListSyntax* statements) noexcept;

    virtual ~DelphiFinallyClauseSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* finallyKeyword() const noexcept { return _pFinallyKeyword; }
    inline DelphiStatementListSyntax* statements() const noexcept { return _pStatements; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pFinallyKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pStatements); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiFinallyClauseSyntax"; }

    static DelphiFinallyClauseSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* finallyKeyword,
                                             DelphiStatementListSyntax* statements) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pFinallyKeyword;
    DelphiStatementListSyntax* _pStatements;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIFINALLYCLAUSESYNTAX_H
