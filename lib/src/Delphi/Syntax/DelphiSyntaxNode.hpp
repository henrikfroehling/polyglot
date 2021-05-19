#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXNODE_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXNODE_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxNode : public Core::Syntax::SyntaxNode
{
public:
    explicit DelphiSyntaxNode(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSyntaxNode() noexcept {}
    inline Core::LanguageKind languageKind() const noexcept override { return Core::LanguageKind::Delphi; }

    virtual std::string typeName() const noexcept override { return "DelphiSyntaxNode"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXNODE_H
