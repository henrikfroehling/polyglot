#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIELSECLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIELSECLAUSESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiElseClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiElseClauseSyntax(Core::Syntax::ISyntaxToken* elseKeyword,
                                    DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiElseClauseSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pElseKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pStatement); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiElseClauseSyntax"; }

    static DelphiElseClauseSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                          Core::Syntax::ISyntaxToken* elseKeyword,
                                          DelphiStatementSyntax* statement) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pElseKeyword;
    DelphiStatementSyntax* _pStatement;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIELSECLAUSESYNTAX_H
