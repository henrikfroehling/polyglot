#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/TokenInfo.hpp"
#include "Core/Syntax/SyntaxList.hpp"
#include "Core/Syntax/SyntaxMissingToken.hpp"
#include "Core/Syntax/SyntaxNode.hpp"
#include "Core/Syntax/SyntaxPool.hpp"
#include "Core/Syntax/SyntaxToken.hpp"
#include "Core/Syntax/SyntaxTrivia.hpp"
#include "Core/Syntax/SyntaxTriviaList.hpp"

namespace polyglot::Core::Syntax
{

using Core::Parser::TokenInfo;

SyntaxFactory::SyntaxFactory(SyntaxPool& syntaxPool) noexcept
    : _syntaxPool{syntaxPool}
{}

ISyntaxToken* SyntaxFactory::token(TokenInfo& tokenInfo,
                                   pg_size position) noexcept
{
    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position);
}

ISyntaxToken* SyntaxFactory::missingToken(SyntaxKind syntaxKind,
                                          std::string_view text,
                                          pg_size position) noexcept
{
    auto ptrMissingToken = std::make_unique<SyntaxMissingToken>(syntaxKind, text, position, text.length());
    return _syntaxPool.addSyntaxToken(std::move(ptrMissingToken));
}

ISyntaxToken* SyntaxFactory::tokenWithTrivia(TokenInfo& tokenInfo,
                                             std::vector<ISyntaxTrivia*>&& leadingTrivia,
                                             std::vector<ISyntaxTrivia*>&& trailingTrivia,
                                             pg_size position) noexcept
{
    ISyntaxTriviaList* pLeadingTrivia{nullptr};
    ISyntaxTriviaList* pTrailingTrivia{nullptr};

    if (!leadingTrivia.empty())
        pLeadingTrivia = _syntaxPool.createSyntaxTriviaList(std::move(leadingTrivia));

    if (!trailingTrivia.empty())
        pTrailingTrivia = _syntaxPool.createSyntaxTriviaList(std::move(trailingTrivia));

    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, pLeadingTrivia, pTrailingTrivia);
}

ISyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                    std::vector<ISyntaxTrivia*>&& leadingTrivia,
                                                    pg_size position) noexcept
{
    ISyntaxTriviaList* pLeadingTrivia = nullptr;

    if (!leadingTrivia.empty())
        pLeadingTrivia = _syntaxPool.createSyntaxTriviaList(std::move(leadingTrivia));

    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, pLeadingTrivia);
}

ISyntaxToken* SyntaxFactory::tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                                    std::string_view text,
                                                    pg_size position,
                                                    ISyntaxTriviaList* leadingTrivia) noexcept
{
    return _syntaxPool.createSyntaxToken(syntaxKind, text, position, leadingTrivia);
}

ISyntaxToken* SyntaxFactory::tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                     std::vector<ISyntaxTrivia*>&& trailingTrivia,
                                                     pg_size position) noexcept
{
    ISyntaxTriviaList* pTrailingTrivia = nullptr;

    if (!trailingTrivia.empty())
        pTrailingTrivia = _syntaxPool.createSyntaxTriviaList(std::move(trailingTrivia));

    return _syntaxPool.createSyntaxToken(tokenInfo.kind, tokenInfo.text, position, nullptr, pTrailingTrivia);
}
                                             
ISyntaxTrivia* SyntaxFactory::endOfLine(std::string_view text,
                                        pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::EndOfLineTrivia, text, position);
}

ISyntaxTrivia* SyntaxFactory::whiteSpace(std::string_view text,
                                         pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::WhitespaceTrivia, text, position);
}

ISyntaxTrivia* SyntaxFactory::singleLineComment(std::string_view text,
                                                pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::SingleLineCommentTrivia, text, position);
}

ISyntaxTrivia* SyntaxFactory::multiLineComment(std::string_view text,
                                               pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(SyntaxKind::MultiLineCommentTrivia, text, position);
}

ISyntaxTrivia* SyntaxFactory::createSyntaxTrivia(SyntaxKind syntaxKind,
                                                 std::string_view text,
                                                 pg_size position) noexcept
{
    return _syntaxPool.createSyntaxTrivia(syntaxKind, text, position);
}

ISyntaxList* SyntaxFactory::syntaxList(SyntaxKind syntaxKind,
                                       std::vector<SyntaxVariant>&& syntaxNodes) noexcept
{
    return _syntaxPool.createSyntaxList(syntaxKind, std::move(syntaxNodes));
}

ISyntaxTriviaList* SyntaxFactory::syntaxTriviaList(std::initializer_list<ISyntaxTrivia*> trivia,
                                                   ISyntaxToken* token) noexcept
{
    return _syntaxPool.createSyntaxTriviaList(std::move(trivia), token);
}

ISyntaxList* SyntaxFactory::addSyntaxList(UniquePtr<ISyntaxList>&& syntaxList) noexcept
{
    return _syntaxPool.addSyntaxList(std::move(syntaxList));
}

ISyntaxNode* SyntaxFactory::addSyntaxNode(UniquePtr<ISyntaxNode>&& syntaxNode) noexcept
{
    return _syntaxPool.addSyntaxNode(std::move(syntaxNode));
}

ISyntaxToken* SyntaxFactory::addSyntaxToken(UniquePtr<ISyntaxToken>&& syntaxToken) noexcept
{
    return _syntaxPool.addSyntaxToken(std::move(syntaxToken));
}

ISyntaxTrivia* SyntaxFactory::addSyntaxTrivia(UniquePtr<ISyntaxTrivia>&& syntaxTrivia) noexcept
{
    return _syntaxPool.addSyntaxTrivia(std::move(syntaxTrivia));
}

ISyntaxTriviaList* SyntaxFactory::addSyntaxTriviaList(UniquePtr<ISyntaxTriviaList>&& syntaxTriviaList) noexcept
{
    return _syntaxPool.addSyntaxTriviaList(std::move(syntaxTriviaList));
}

} // end namespace polyglot::Core::Syntax
