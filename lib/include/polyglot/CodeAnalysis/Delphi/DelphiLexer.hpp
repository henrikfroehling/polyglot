#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(std::string code) noexcept;
    SyntaxToken nextToken() noexcept override final;

private:
    void lexStringLiteral(SyntaxToken& token) noexcept;
    void lexNumberLiteral(SyntaxToken& token) noexcept;
    void lexWhiteSpace(SyntaxToken& token) noexcept;
    void lexIdentifierOrKeyword(SyntaxToken& token) noexcept;

private:
    pg_size _start;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
