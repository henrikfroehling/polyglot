#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICASEELSECLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICASEELSECLAUSESYNTAX_H

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

class DelphiCaseElseClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCaseElseClauseSyntax(Core::Syntax::ISyntaxToken* elseKeyword,
                                        DelphiStatementListSyntax* statements) noexcept;

    virtual ~DelphiCaseElseClauseSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline DelphiStatementListSyntax* statements() const noexcept { return _pStatements; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pElseKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pStatements); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseElseClauseSyntax"; }

    static DelphiCaseElseClauseSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* elseKeyword,
                                              DelphiStatementListSyntax* statements) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pElseKeyword;
    DelphiStatementListSyntax* _pStatements;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICASEELSECLAUSESYNTAX_H
