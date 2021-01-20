#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxToken* SyntaxFactory::token(TokenInfo& tokenInfo,
                                  pg_size position) noexcept
{
    return SyntaxPool::createSyntaxToken(tokenInfo.kind, tokenInfo.text, position);
}

SyntaxToken* SyntaxFactory::tokenWithTrivia(TokenInfo& tokenInfo,
                                            std::vector<SyntaxTrivia*>&& leadingTrivia,
                                            std::vector<SyntaxTrivia*>&& trailingTrivia,
                                            pg_size position) noexcept
{
    SyntaxToken* pSyntaxToken = token(tokenInfo, position);
    pSyntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    pSyntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return pSyntaxToken;
}

SyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                   std::vector<SyntaxTrivia*>&& leadingTrivia,
                                                   pg_size position) noexcept
{
    SyntaxToken* pSyntaxToken = token(tokenInfo, position);
    pSyntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    return pSyntaxToken;
}

SyntaxToken* SyntaxFactory::tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                    std::vector<SyntaxTrivia*>&& trailingTrivia,
                                                    pg_size position) noexcept
{
    SyntaxToken* pSyntaxToken = token(tokenInfo, position);
    pSyntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return pSyntaxToken;
}
                                             
SyntaxTrivia* SyntaxFactory::endOfLine(std::string_view text,
                                             pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::EndOfLineTrivia, text, position);
}

SyntaxTrivia* SyntaxFactory::whiteSpace(std::string_view text,
                                              pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::WhitespaceTrivia, text, position);
}

SyntaxTrivia* SyntaxFactory::singleLineComment(std::string_view text,
                                              pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::SingleLineCommentTrivia, text, position);
}

SyntaxTrivia* SyntaxFactory::multiLineComment(std::string_view text,
                                             pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::MultiLineCommentTrivia, text, position);
}

} // end namespace polyglot::CodeAnalysis
