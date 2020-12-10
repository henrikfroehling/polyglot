#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;
class SyntaxTrivia;

class POLYGLOT_API DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(SharedPtr<SourceText> sourceText) noexcept;

private:
    SyntaxToken* lex(LexerMode mode) noexcept override;
    TokenInfo quickScanSyntaxToken() noexcept;
    TokenInfo lexSyntaxToken() noexcept;
    TokenInfo lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool afterFirstToken,
                         bool isTrailing,
                         std::vector<SyntaxNode*>& triviaList) noexcept;

    SyntaxTrivia* scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    SyntaxTrivia* scanEndOfLine() noexcept;
    void scanSyntaxToken(TokenInfo& tokenInfo) noexcept;
    void scanStringLiteral(TokenInfo& tokenInfo) noexcept;
    void scanIdentifierOrKeyword(TokenInfo& tokenInfo) noexcept;

    void scanIdentifierOrKeyword(std::string_view chars,
                                 TokenInfo& tokenInfo) noexcept;

    bool scanIdentifier(TokenInfo& token) noexcept;
    void scanNumericLiteral(TokenInfo& tokenInfo) noexcept;

    void lexDirectiveAndExcludedTrivia(bool afterFirstToken,
                                       bool afterNonWhitespaceOnLine,
                                       std::vector<SyntaxNode*>& triviaList) noexcept;

    SyntaxNode* lexSingleDirective(bool isActive,
                                   bool endIsActive,
                                   bool afterFirstToken,
                                   bool afterNonWhitespaceOnLine,
                                   std::vector<SyntaxNode*>& triviaList) noexcept;

    void lexExludedDirectivesAndTrivia(bool endIsActive) noexcept;
    SyntaxToken* lexDirectiveToken() noexcept;
    void scanDirectiveToken(TokenInfo& tokenInfo) noexcept;
    void lexDirectiveTrailingTrivia(bool includeEndOfLine) noexcept;
    SyntaxNode* lexDirectiveTrivia() noexcept;

private:
    pg_size _currentTriviaPosition;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
