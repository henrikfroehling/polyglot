#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiNameExpressionSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(DelphiNameExpressionSyntax* unitName,
                                                  Core::Syntax::ISyntaxToken* inKeyword = nullptr,
                                                  Core::Syntax::ISyntaxToken* sourceFile = nullptr) noexcept;

    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept {}
    inline DelphiNameExpressionSyntax* unitName() const noexcept { return _pUnitName; }
    inline Core::Syntax::ISyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline Core::Syntax::ISyntaxToken* sourceFile() const noexcept { return _pSourceFile; }
    inline pg_size childCount() const noexcept override final { return _pSourceFile != nullptr ? 3 : 1; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pUnitName); }

    inline Core::Syntax::SyntaxVariant last() const noexcept override final
    {
        if (_pSourceFile != nullptr)
            return Core::Syntax::SyntaxVariant::asToken(_pSourceFile);

        return Core::Syntax::SyntaxVariant::asNode(_pUnitName);
    }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiUnitReferenceDeclarationSyntax"; }

    static DelphiUnitReferenceDeclarationSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                        DelphiNameExpressionSyntax* unitName,
                                                        Core::Syntax::ISyntaxToken* inKeyword = nullptr,
                                                        Core::Syntax::ISyntaxToken* sourceFile = nullptr) noexcept;

private:
    DelphiNameExpressionSyntax* _pUnitName;
    Core::Syntax::ISyntaxToken* _pInKeyword; // optional
    Core::Syntax::ISyntaxToken* _pSourceFile; // optional, but needs _pInKeyword
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
