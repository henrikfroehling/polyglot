#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

LanguageSyntaxToken* SyntaxFactory::token(TokenInfo& tokenInfo,
                                          pg_size position) noexcept
{
    return SyntaxPool::createSyntaxToken(tokenInfo.kind, tokenInfo.text, position);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithTrivia(TokenInfo& tokenInfo,
                                                    std::vector<LanguageSyntaxTrivia*>&& leadingTrivia,
                                                    std::vector<LanguageSyntaxTrivia*>&& trailingTrivia,
                                                    pg_size position) noexcept
{
    LanguageSyntaxToken* pSyntaxToken = token(tokenInfo, position);
    // TODO
    //pSyntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    //pSyntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return pSyntaxToken;
}

LanguageSyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                           std::vector<LanguageSyntaxTrivia*>&& leadingTrivia,
                                                           pg_size position) noexcept
{
    LanguageSyntaxToken* pSyntaxToken = token(tokenInfo, position);
    // TODO
    //pSyntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    return pSyntaxToken;
}

LanguageSyntaxToken* SyntaxFactory::tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                            std::vector<LanguageSyntaxTrivia*>&& trailingTrivia,
                                                            pg_size position) noexcept
{
    LanguageSyntaxToken* pSyntaxToken = token(tokenInfo, position);
    // TODO
    //pSyntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return pSyntaxToken;
}
                                             
LanguageSyntaxTrivia* SyntaxFactory::endOfLine(std::string_view text,
                                               pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::EndOfLineTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::whiteSpace(std::string_view text,
                                                pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::WhitespaceTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::singleLineComment(std::string_view text,
                                                       pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::SingleLineCommentTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::multiLineComment(std::string_view text,
                                                      pg_size position) noexcept
{
    return SyntaxPool::createSyntaxTrivia(SyntaxKind::MultiLineCommentTrivia, text, position);
}

} // end namespace polyglot::CodeAnalysis
