#ifndef POLYGLOT_DELPHI_PARSER_DELPHILEXER_H
#define POLYGLOT_DELPHI_PARSER_DELPHILEXER_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/Lexer.hpp"
#include "Core/Parser/TokenInfo.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class ISyntaxTrivia;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Parser
{

class DelphiLexer final : public Core::Parser::Lexer
{
public:
    explicit DelphiLexer(SharedPtr<Core::Text::SourceText> sourceText) noexcept;

private:
    Core::Syntax::ISyntaxToken* lexToken() noexcept override;
    Core::Parser::TokenInfo quickScanSyntaxToken() noexcept;
    Core::Parser::TokenInfo lexSyntaxToken() noexcept;
    Core::Parser::TokenInfo lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool afterFirstToken,
                         bool isTrailing,
                         std::vector<Core::Syntax::ISyntaxTrivia*>& triviaList) noexcept;

    Core::Syntax::ISyntaxTrivia* scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    Core::Syntax::ISyntaxTrivia* scanEndOfLine() noexcept;
    void scanSyntaxToken(Core::Parser::TokenInfo& tokenInfo) noexcept;
    void scanStringLiteral(Core::Parser::TokenInfo& tokenInfo) noexcept;
    void scanIdentifierOrKeyword(Core::Parser::TokenInfo& tokenInfo) noexcept;

    void scanIdentifierOrKeyword(std::string_view chars,
                                 Core::Parser::TokenInfo& tokenInfo) noexcept;

    bool scanIdentifier(Core::Parser::TokenInfo& token) noexcept;
    void scanNumericLiteral(Core::Parser::TokenInfo& tokenInfo) noexcept;

    void lexSingleDirective(bool isActive,
                            bool endIsActive,
                            bool afterFirstToken,
                            bool afterNonWhitespaceOnLine,
                            std::vector<Core::Syntax::ISyntaxTrivia*>& triviaList) noexcept;

    Core::Syntax::ISyntaxToken* lexDirectiveToken() noexcept;
    void scanDirectiveToken(Core::Parser::TokenInfo& tokenInfo) noexcept;

    void lexDirectiveTrailingTrivia(std::vector<Core::Syntax::ISyntaxTrivia*>& triviaList,
                                    bool includeEndOfLine) noexcept;

    Core::Syntax::ISyntaxTrivia* lexDirectiveTrivia() noexcept;
    Core::Syntax::ISyntaxTrivia* scanDirectiveWhitespace() noexcept;

private:
    pg_size _currentTriviaPosition;
    Core::Syntax::SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHILEXER_H
