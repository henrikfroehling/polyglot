#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXLIST_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxList.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxList : public Core::Syntax::SyntaxList
{
public:
    explicit DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSyntaxList() noexcept {}
    inline Core::LanguageKind languageKind() const noexcept override { return Core::LanguageKind::Delphi; }

    virtual pg_string typeName() const noexcept override { return L"DelphiSyntaxList"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
