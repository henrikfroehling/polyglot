#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Parser/TokenInfo.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxMissingToken.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxFactory::SyntaxFactory(SyntaxPool& syntaxPool) noexcept
    : _syntaxPool{syntaxPool}
{}

LanguageSyntaxToken* SyntaxFactory::token(TokenInfo& tokenInfo,
                                          pg_size position) noexcept
{
    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position);
}

LanguageSyntaxToken* SyntaxFactory::missingToken(SyntaxKind syntaxKind,
                                                 std::string_view text,
                                                 pg_size position) noexcept
{
    auto ptrMissingToken = std::make_unique<LanguageSyntaxMissingToken>(syntaxKind, text, position, text.length());
    return _syntaxPool.addSyntaxToken(std::move(ptrMissingToken));
}

LanguageSyntaxToken* SyntaxFactory::tokenWithTrivia(TokenInfo& tokenInfo,
                                                    std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                    std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                    pg_size position) noexcept
{
    LanguageSyntaxList* pLeadingTrivia = _syntaxPool.createSyntaxList(std::move(leadingTrivia));
    LanguageSyntaxList* pTrailingTrivia = _syntaxPool.createSyntaxList(std::move(trailingTrivia));
    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, pLeadingTrivia, pTrailingTrivia);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                           std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                           pg_size position) noexcept
{
    LanguageSyntaxList* pLeadingTrivia = _syntaxPool.createSyntaxList(std::move(leadingTrivia));
    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, pLeadingTrivia);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                                           std::string_view text,
                                                           pg_size position,
                                                           LanguageSyntaxList* leadingTrivia) noexcept
{
    return _syntaxPool.createSyntaxToken(syntaxKind, text, position, leadingTrivia);
}

LanguageSyntaxToken* SyntaxFactory::tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                            std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                            pg_size position) noexcept
{
    LanguageSyntaxList* pTrailingTrivia = _syntaxPool.createSyntaxList(std::move(trailingTrivia));
    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, nullptr, pTrailingTrivia);
}
                                             
LanguageSyntaxTrivia* SyntaxFactory::endOfLine(std::string_view text,
                                               pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::EndOfLineTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::whiteSpace(std::string_view text,
                                                pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::WhitespaceTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::singleLineComment(std::string_view text,
                                                       pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::SingleLineCommentTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::multiLineComment(std::string_view text,
                                                      pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::MultiLineCommentTrivia, text, position);
}

LanguageSyntaxTrivia* SyntaxFactory::createSyntaxTrivia(SyntaxKind syntaxKind,
                                                        std::string_view text,
                                                        pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(syntaxKind, text, position);
}

LanguageSyntaxList* SyntaxFactory::syntaxList(std::initializer_list<LanguageSyntaxNode*> syntaxNodes) noexcept
{
    return _syntaxPool.createSyntaxList(std::move(syntaxNodes));
}

LanguageSyntaxNode* SyntaxFactory::addSyntaxNode(UniquePtr<LanguageSyntaxNode>&& syntaxNode) noexcept
{
    return _syntaxPool.addSyntaxNode(std::move(syntaxNode));
}

LanguageSyntaxToken* SyntaxFactory::addSyntaxToken(UniquePtr<LanguageSyntaxToken>&& syntaxToken) noexcept
{
    return _syntaxPool.addSyntaxToken(std::move(syntaxToken));
}

LanguageSyntaxTrivia* SyntaxFactory::addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia>&& syntaxTrivia) noexcept
{
    return _syntaxPool.addSyntaxTrivia(std::move(syntaxTrivia));
}

} // end namespace polyglot::CodeAnalysis
