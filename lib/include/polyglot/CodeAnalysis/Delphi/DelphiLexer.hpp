#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(const SourceText& sourceText) noexcept;
    SyntaxToken nextToken() noexcept override final;

private:
    void lexSyntaxTrivia(bool isTrailing, std::vector<SyntaxTrivia>& triviaList) noexcept;
    SyntaxTrivia scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    SyntaxTrivia scanEndOfLine() noexcept;
    void scanSyntaxToken(SyntaxToken& token) noexcept;
    void scanStringLiteral(SyntaxToken& token) noexcept;
    void scanIdentifierOrKeyword(SyntaxToken& token) noexcept;
    bool scanIdentifier(SyntaxToken& token) noexcept;
    void scanNumericLiteral(SyntaxToken& token) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
