#include "CodeAnalysis/Delphi/DelphiSyntaxFactory.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxToken* DelphiSyntaxFactory::createToken(TokenInfo& tokenInfo,
                                              pg_size position) noexcept
{
    SyntaxToken* syntaxToken = SyntaxPool::createSyntaxToken();
    syntaxToken->setSyntaxKind(tokenInfo.kind);
    syntaxToken->setText(tokenInfo.text);
    syntaxToken->setPosition(position);
    return syntaxToken;
}

SyntaxToken* DelphiSyntaxFactory::createTokenWithTrivia(TokenInfo& tokenInfo,
                                                        pg_size position,
                                                        std::vector<SyntaxTrivia*>&& leadingTrivia,
                                                        std::vector<SyntaxTrivia*>&& trailingTrivia) noexcept
{
    SyntaxToken* syntaxToken = createToken(tokenInfo, position);
    syntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    syntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return syntaxToken;
}

SyntaxToken* DelphiSyntaxFactory::createTokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                               pg_size position,
                                                               std::vector<SyntaxTrivia*>&& leadingTrivia) noexcept
{
    SyntaxToken* syntaxToken = createToken(tokenInfo, position);
    syntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    return syntaxToken;
}

SyntaxToken* DelphiSyntaxFactory::createTokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                                pg_size position,
                                                                std::vector<SyntaxTrivia*>&& trailingTrivia) noexcept
{
    SyntaxToken* syntaxToken = createToken(tokenInfo, position);
    syntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return syntaxToken;
}

SyntaxTrivia* DelphiSyntaxFactory::createTrivia(SyntaxKind syntaxKind,
                                                std::string_view text,
                                                pg_size position) noexcept
{
    SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
    syntaxTrivia->setSyntaxKind(syntaxKind);
    syntaxTrivia->setText(text);
    syntaxTrivia->setPosition(position);
    return syntaxTrivia;
}

} // end namespace polyglot::CodeAnalysis
