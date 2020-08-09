#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <memory>
#include <string_view>
#include <vector>
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
    std::shared_ptr<SyntaxToken> nextToken() noexcept override final;

private:
    std::shared_ptr<SyntaxToken> quickScanSyntaxToken() noexcept;
    std::shared_ptr<SyntaxToken> lexSyntaxToken() noexcept;
    std::shared_ptr<SyntaxToken> lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool isTrailing,
                         bool needsStart = true) noexcept;

    std::shared_ptr<SyntaxTrivia> scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    std::shared_ptr<SyntaxTrivia> scanEndOfLine() noexcept;
    void scanSyntaxToken(SyntaxToken& token) noexcept;
    void scanStringLiteral(SyntaxToken& token) noexcept;
    void scanIdentifierOrKeyword(SyntaxToken& token) noexcept;

    void scanIdentifierOrKeyword(std::string_view chars,
                                 SyntaxToken& token) noexcept;

    bool scanIdentifier(SyntaxToken& token) noexcept;
    void scanNumericLiteral(SyntaxToken& token) noexcept;

private:
    std::vector<std::shared_ptr<SyntaxTrivia>> _leadingTrivia;
    std::vector<std::shared_ptr<SyntaxTrivia>> _trailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
