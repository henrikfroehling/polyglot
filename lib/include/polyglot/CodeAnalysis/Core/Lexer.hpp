#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SlidingTextWindow.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API Lexer
{
public:
    virtual ~Lexer();
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    virtual std::unique_ptr<SyntaxToken> nextToken() noexcept = 0;

protected:
    explicit Lexer(SourceText* sourceText) noexcept;
    void start() noexcept;

protected:
    SlidingTextWindow _textWindow;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H
