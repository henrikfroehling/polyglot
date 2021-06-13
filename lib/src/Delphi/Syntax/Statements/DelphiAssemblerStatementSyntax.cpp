#include "Delphi/Syntax/Statements/DelphiAssemblerStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiAssemblerStatementSyntax::DelphiAssemblerStatementSyntax(ISyntaxToken* asmKeyword,
                                                               ISyntaxToken* endKeyword,
                                                               ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::AssemblerStatement},
      _pAsmKeyword{asmKeyword},
      _pEndKeyword{endKeyword},
      _pSemiColonToken{semiColonToken}
{}

SyntaxVariant DelphiAssemblerStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pAsmKeyword);
        case 1: return SyntaxVariant::asToken(_pEndKeyword);
        case 2: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiAssemblerStatementSyntax* DelphiAssemblerStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                       ISyntaxToken* asmKeyword,
                                                                       ISyntaxToken* endKeyword,
                                                                       ISyntaxToken* semiColonToken) noexcept
{
    assert(asmKeyword != nullptr);
    assert(asmKeyword->syntaxKind() == SyntaxKind::AsmKeyword);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrAssemblerStatementSyntax = std::make_unique<DelphiAssemblerStatementSyntax>(asmKeyword, endKeyword, semiColonToken);
    return static_cast<DelphiAssemblerStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrAssemblerStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
