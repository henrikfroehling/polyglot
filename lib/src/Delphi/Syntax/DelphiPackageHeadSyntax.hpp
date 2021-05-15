#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEHEADSYNTAX_H

#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax;

namespace polyglot::Delphi::Syntax
{

class DelphiPackageHeadSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageHeadSyntax() noexcept;
    virtual ~DelphiPackageHeadSyntax() noexcept {}

    virtual Core::Syntax::ISyntaxToken* firstToken() const noexcept override { return nullptr; }
    virtual Core::Syntax::ISyntaxToken* lastToken() const noexcept override { return nullptr; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEHEADSYNTAX_H
