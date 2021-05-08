#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXLIST_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxList.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxList : public SyntaxList
{
public:
    explicit DelphiSyntaxList(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSyntaxList() noexcept = default;
    inline LanguageKind languageKind() const noexcept override { return LanguageKind::Delphi; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
