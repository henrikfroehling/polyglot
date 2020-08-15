#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(SourceText* sourceText) noexcept;
    SyntaxTokenPtr nextToken() noexcept override final;

private:
    SyntaxTokenPtr quickScanSyntaxToken() noexcept override;
    SyntaxTokenPtr lexSyntaxToken() noexcept;
    SyntaxTokenPtr lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool isTrailing,
                         bool needsStart = true) noexcept;

    SyntaxTriviaPtr scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    SyntaxTriviaPtr scanEndOfLine() noexcept;
    void scanSyntaxToken(SyntaxToken& token) noexcept;
    void scanStringLiteral(SyntaxToken& token) noexcept;
    void scanIdentifierOrKeyword(SyntaxToken& token) noexcept;

    void scanIdentifierOrKeyword(std::string_view chars,
                                 SyntaxToken& token) noexcept;

    bool scanIdentifier(SyntaxToken& token) noexcept;
    void scanNumericLiteral(SyntaxToken& token) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
