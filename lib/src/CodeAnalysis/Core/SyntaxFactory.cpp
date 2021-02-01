#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Parser/TokenInfo.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxMissingToken.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

LanguageSyntaxToken* SyntaxFactory::token(TokenInfo& tokenInfo,
                                          pg_size position) noexcept
{
    return SyntaxPool::createSyntaxToken(tokenInfo.kind, tokenInfo.text, position);
}

LanguageSyntaxToken* SyntaxFactory::missingToken(SyntaxKind syntaxKind,
                                                 std::string_view text,
                                                 pg_size position) noexcept
{
    auto ptrMissingToken = std::make_unique<LanguageSyntaxMissingToken>(syntaxKind, text, position, text.length());
    return SyntaxPool::addSyntaxToken(std::move(ptrMissingToken));
}

LanguageSyntaxToken* SyntaxFactory::tokenWithTrivia(TokenInfo& tokenInfo,
                                                    std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                    std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                    pg_size position) noexcept
{
    LanguageSyntaxList* pLeadingTrivia = SyntaxPool::createSyntaxList(std::move(leadingTrivia));
    LanguageSyntaxList* pTrailingTrivia = SyntaxPool::createSyntaxList(std::move(trailingTrivia));
    return SyntaxPool::createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, pLeadingTrivia, pTrailingTrivia);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                           std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                           pg_size position) noexcept
{
    LanguageSyntaxList* pLeadingTrivia = SyntaxPool::createSyntaxList(std::move(leadingTrivia));
    return SyntaxPool::createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, pLeadingTrivia);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                                           std::string_view text,
                                                           pg_size position,
                                                           LanguageSyntaxList* leadingTrivia) noexcept
{
    return SyntaxPool::createSyntaxToken(syntaxKind, text, position, leadingTrivia);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                            std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                            pg_size position) noexcept
{
    LanguageSyntaxList* pTrailingTrivia = SyntaxPool::createSyntaxList(std::move(trailingTrivia));
    return SyntaxPool::createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, nullptr, pTrailingTrivia);
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

LanguageSyntaxList* SyntaxFactory::syntaxList(std::initializer_list<LanguageSyntaxNode*> syntaxNodes) noexcept
{
    return SyntaxPool::createSyntaxList(std::move(syntaxNodes));
}

} // end namespace polyglot::CodeAnalysis
