#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"

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
    SyntaxToken* syntaxToken = token(tokenInfo, position);
    syntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    syntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return syntaxToken;
}

SyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                   std::vector<SyntaxTrivia*>&& leadingTrivia,
                                                   pg_size position) noexcept
{
    SyntaxToken* syntaxToken = token(tokenInfo, position);
    syntaxToken->setLeadingTrivia(std::move(leadingTrivia));
    return syntaxToken;
}

SyntaxToken* SyntaxFactory::tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                    std::vector<SyntaxTrivia*>&& trailingTrivia,
                                                    pg_size position) noexcept
{
    SyntaxToken* syntaxToken = token(tokenInfo, position);
    syntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return syntaxToken;
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
