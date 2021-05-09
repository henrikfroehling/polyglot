#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "DelphiSyntaxList.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitReferenceDeclarationSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiUnitReferenceDeclarationSyntax(Core::Syntax::NameExpressionSyntax* unitName,
                                                  Core::Syntax::ISyntaxToken* inKeyword = nullptr,
                                                  Core::Syntax::ISyntaxToken* sourceFile = nullptr) noexcept;

    virtual ~DelphiUnitReferenceDeclarationSyntax() noexcept {}
    inline Core::Syntax::NameExpressionSyntax* unitName() const noexcept { return _pUnitName; }
    inline Core::Syntax::ISyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline Core::Syntax::ISyntaxToken* sourceFile() const noexcept { return _pSourceFile; }
    inline pg_size childCount() const noexcept override final { return _pSourceFile != nullptr ? 3 : 1; }
    Core::Syntax::SyntaxNodeOrToken child(pg_size index) const override final;

    inline Core::Syntax::SyntaxNodeOrToken first() const noexcept override final { return Core::Syntax::SyntaxNodeOrToken::asNode(_pUnitName); }

    inline Core::Syntax::SyntaxNodeOrToken last() const noexcept override final
    {
        if (_pSourceFile != nullptr)
            return Core::Syntax::SyntaxNodeOrToken::asToken(_pSourceFile);

        return Core::Syntax::SyntaxNodeOrToken::asNode(_pUnitName);
    }

    static DelphiUnitReferenceDeclarationSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                        Core::Syntax::NameExpressionSyntax* unitName,
                                                        Core::Syntax::ISyntaxToken* inKeyword = nullptr,
                                                        Core::Syntax::ISyntaxToken* sourceFile = nullptr) noexcept;

private:
    Core::Syntax::NameExpressionSyntax* _pUnitName;
    Core::Syntax::ISyntaxToken* _pInKeyword; // optional
    Core::Syntax::ISyntaxToken* _pSourceFile; // optional, but needs _pInKeyword
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITREFERENCEDECLARATIONSYNTAX_H
