#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTCLAUSESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTCLAUSESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiExceptionBlockSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExceptClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiExceptClauseSyntax(Core::Syntax::ISyntaxToken* exceptKeyword,
                                      DelphiExceptionBlockSyntax* exceptionBlock) noexcept;

    virtual ~DelphiExceptClauseSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* exceptKeyword() const noexcept { return _pExceptKeyword; }
    inline DelphiExceptionBlockSyntax* exceptionBlock() const noexcept { return _pExceptionBlock; }

    inline pg_size childCount() const noexcept override final { return 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pExceptKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pExceptionBlock); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExceptClauseSyntax"; }

    static DelphiExceptClauseSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                            Core::Syntax::ISyntaxToken* exceptKeyword,
                                            DelphiExceptionBlockSyntax* exceptionBlock) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pExceptKeyword;
    DelphiExceptionBlockSyntax* _pExceptionBlock;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIEXCEPTCLAUSESYNTAX_H
