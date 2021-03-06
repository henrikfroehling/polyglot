#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H

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

class DelphiNameSyntax;

class DelphiUnitHeadSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadSyntax(Core::Syntax::ISyntaxToken* unitKeyword,
                                  DelphiNameSyntax* name,
                                  Core::Syntax::ISyntaxToken* semiColonToken,
                                  Core::Syntax::ISyntaxToken* inKeyword = nullptr,
                                  Core::Syntax::ISyntaxToken* filename = nullptr) noexcept;

    virtual ~DelphiUnitHeadSyntax() noexcept {}
    inline Core::Syntax::ISyntaxToken* unitKeyword() const noexcept { return _pUnitKeyword; }
    inline DelphiNameSyntax* name() const noexcept { return _pName; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }
    inline Core::Syntax::ISyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline Core::Syntax::ISyntaxToken* filename() const noexcept { return _pFilename; }
    inline pg_size childCount() const noexcept override final { return _pFilename != nullptr ? 5 : 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pUnitKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiUnitHeadSyntax"; }

    static DelphiUnitHeadSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                        Core::Syntax::ISyntaxToken* unitKeyword,
                                        DelphiNameSyntax* name,
                                        Core::Syntax::ISyntaxToken* semiColonToken,
                                        Core::Syntax::ISyntaxToken* inKeyword = nullptr,
                                        Core::Syntax::ISyntaxToken* filename = nullptr) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pUnitKeyword;
    DelphiNameSyntax* _pName;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
    Core::Syntax::ISyntaxToken* _pInKeyword; // optional
    Core::Syntax::ISyntaxToken* _pFilename; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
