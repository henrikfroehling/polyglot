#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(SourceTextPtr sourceText) noexcept;

private:
    SyntaxTokenPtr lex(LexerMode mode) noexcept override;
    TokenInfo quickScanSyntaxToken() noexcept;
    TokenInfo lexSyntaxToken() noexcept;
    TokenInfo lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool afterFirstToken,
                         bool isTrailing,
                         std::vector<SyntaxNodePtr>& triviaList) noexcept;

    SyntaxTriviaPtr scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    SyntaxTriviaPtr scanEndOfLine() noexcept;
    void scanSyntaxToken(TokenInfo& tokenInfo) noexcept;
    void scanStringLiteral(TokenInfo& tokenInfo) noexcept;
    void scanIdentifierOrKeyword(TokenInfo& tokenInfo) noexcept;

    void scanIdentifierOrKeyword(std::string_view chars,
                                 TokenInfo& tokenInfo) noexcept;

    bool scanIdentifier(TokenInfo& token) noexcept;
    void scanNumericLiteral(TokenInfo& tokenInfo) noexcept;

    void lexDirectiveAndExcludedTrivia(bool afterFirstToken,
                                       bool afterNonWhitespaceOnLine,
                                       std::vector<SyntaxNodePtr>& triviaList) noexcept;

    SyntaxNodePtr lexSingleDirective(bool isActive,
                                     bool endIsActive,
                                     bool afterFirstToken,
                                     bool afterNonWhitespaceOnLine,
                                     std::vector<SyntaxNodePtr>& triviaList) noexcept;

    void lexExludedDirectivesAndTrivia(bool endIsActive) noexcept;
    SyntaxTokenPtr lexDirectiveToken() noexcept;
    void scanDirectiveToken(TokenInfo& tokenInfo) noexcept;
    void lexDirectiveTrailingTrivia(bool includeEndOfLine) noexcept;
    SyntaxNodePtr lexDirectiveTrivia() noexcept;

private:
    pg_size _currentTriviaPosition;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
