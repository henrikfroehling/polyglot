#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiNameSyntax.hpp"
#include "Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiQualifiedNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiQualifiedNameSyntax(DelphiNameSyntax* left,
                                       Core::Syntax::ISyntaxToken* dotToken,
                                       DelphiSimpleNameSyntax* right) noexcept;

    virtual ~DelphiQualifiedNameSyntax() noexcept {}
    inline virtual DelphiNameSyntax* left() const noexcept { return _pLeft; }
    inline virtual Core::Syntax::ISyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline virtual DelphiSimpleNameSyntax* right() const noexcept { return _pRight; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pLeft); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pRight); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiQualifiedNameSyntax"; }

    static DelphiQualifiedNameSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             DelphiNameSyntax* left,
                                             Core::Syntax::ISyntaxToken* dotToken,
                                             DelphiSimpleNameSyntax* right) noexcept;

private:
    DelphiNameSyntax* _pLeft;
    Core::Syntax::ISyntaxToken* _pDotToken;
    DelphiSimpleNameSyntax* _pRight;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
