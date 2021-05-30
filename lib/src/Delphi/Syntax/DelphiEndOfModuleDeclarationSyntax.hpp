#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIENDOFMODULEDECLARATIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIENDOFMODULEDECLARATIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiEndOfModuleDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiEndOfModuleDeclarationSyntax(Core::Syntax::ISyntaxToken* endKeyword,
                                                Core::Syntax::ISyntaxToken* dotToken) noexcept;

    virtual ~DelphiEndOfModuleDeclarationSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline Core::Syntax::ISyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline pg_size childCount() const noexcept override final { return 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pEndKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pDotToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiEndOfModuleDeclarationSyntax"; }

    static DelphiEndOfModuleDeclarationSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                      Core::Syntax::ISyntaxToken* endKeyword,
                                                      Core::Syntax::ISyntaxToken* dotToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pEndKeyword;
    Core::Syntax::ISyntaxToken* _pDotToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIENDOFMODULEDECLARATIONSYNTAX_H
