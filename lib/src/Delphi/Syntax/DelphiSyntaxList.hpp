#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXLIST_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxList.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxList : public Core::Syntax::SyntaxList
{
public:
    explicit DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind) noexcept;

    explicit DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind,
                              std::vector<Core::Syntax::SyntaxVariant>&& children) noexcept;

    virtual ~DelphiSyntaxList() noexcept {}
    inline Core::LanguageKind languageKind() const noexcept override { return Core::LanguageKind::Delphi; }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSyntaxList"; }

    static DelphiSyntaxList* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                    Core::Syntax::SyntaxKind syntaxKind,
                                    std::vector<Core::Syntax::SyntaxVariant>&& children) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXLIST_H
