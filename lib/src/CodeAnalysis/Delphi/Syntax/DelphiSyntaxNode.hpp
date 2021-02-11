#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXNODE_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiSyntaxNode : public LanguageSyntaxNode
{
public:
    explicit DelphiSyntaxNode(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSyntaxNode() noexcept = default;
    inline LanguageKind languageKind() const noexcept override { return LanguageKind::Delphi; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXNODE_H
