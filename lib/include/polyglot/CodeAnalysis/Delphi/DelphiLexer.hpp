#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
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
    void lexStringLiteral(SyntaxToken& token) noexcept;
    void lexNumberLiteral(SyntaxToken& token) noexcept;
    void lexWhiteSpace(SyntaxToken& token) noexcept;
    void lexIdentifierOrKeyword(SyntaxToken& token) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
