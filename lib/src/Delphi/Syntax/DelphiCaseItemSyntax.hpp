#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICASEITEMSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICASEITEMSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseLabelListSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCaseItemSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCaseItemSyntax(DelphiCaseLabelListSyntax* caseLabels,
                                  Core::Syntax::ISyntaxToken* colonToken,
                                  DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiCaseItemSyntax() noexcept {}

    inline DelphiCaseLabelListSyntax* caseLabels() const noexcept { return _pCaseLabels; }
    inline Core::Syntax::ISyntaxToken* colonToken() const noexcept { return _pColonToken; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pCaseLabels); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pStatement); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseItemSyntax"; }

    static DelphiCaseItemSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                        DelphiCaseLabelListSyntax* caseLabels,
                                        Core::Syntax::ISyntaxToken* colonToken,
                                        DelphiStatementSyntax* statement) noexcept;

private:
    DelphiCaseLabelListSyntax* _pCaseLabels;
    Core::Syntax::ISyntaxToken* _pColonToken;
    DelphiStatementSyntax* _pStatement;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICASEITEMSYNTAX_H
