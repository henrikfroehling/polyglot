#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXNODE_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXNODE_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxNode : public SyntaxNode
{
public:
    explicit DelphiSyntaxNode(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSyntaxNode() noexcept = default;
    inline LanguageKind languageKind() const noexcept override { return LanguageKind::Delphi; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXNODE_H
