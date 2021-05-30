#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIEXTENDEDIDENTIFIERNAMESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIEXTENDEDIDENTIFIERNAMESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExtendedIdentifierNameSyntax : public DelphiSimpleNameSyntax
{
public:
    explicit DelphiExtendedIdentifierNameSyntax(Core::Syntax::ISyntaxToken* ampersandToken,
                                                Core::Syntax::ISyntaxToken* reservedKeyword) noexcept;

    virtual ~DelphiExtendedIdentifierNameSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* ampersandToken() const noexcept { return _pAmpersandToken; }
    inline Core::Syntax::ISyntaxToken* reservedKeyword() const noexcept { return _pReservedKeyword; }

    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pAmpersandToken); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asToken(_pReservedKeyword); }

    inline pg_string typeName() const noexcept override final { return L"DelphiExtendedIdentifierNameSyntax"; }

    static DelphiExtendedIdentifierNameSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                      Core::Syntax::ISyntaxToken* ampersandToken,
                                                      Core::Syntax::ISyntaxToken* reservedKeyword) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pAmpersandToken;
    Core::Syntax::ISyntaxToken* _pReservedKeyword;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIEXTENDEDIDENTIFIERNAMESYNTAX_H
