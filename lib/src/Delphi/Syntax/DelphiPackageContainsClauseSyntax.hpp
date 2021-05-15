#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H

#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax;

namespace polyglot::Delphi::Syntax
{

class DelphiPackageContainsClauseSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageContainsClauseSyntax() noexcept;
    virtual ~DelphiPackageContainsClauseSyntax() noexcept {}

    virtual Core::Syntax::ISyntaxToken* firstToken() const noexcept override { return nullptr; }
    virtual Core::Syntax::ISyntaxToken* lastToken() const noexcept override { return nullptr; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGECONTAINSCLAUSESYNTAX_H
