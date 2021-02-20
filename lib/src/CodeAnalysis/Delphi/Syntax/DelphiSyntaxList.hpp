#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXLIST_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxList.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiSyntaxList : public SyntaxList
{
public:
    explicit DelphiSyntaxList(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSyntaxList() noexcept = default;
    inline LanguageKind languageKind() const noexcept override { return LanguageKind::Delphi; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
