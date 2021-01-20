#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/DirectiveStack.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class SyntaxTrivia
{
public:
    SyntaxTrivia() noexcept;

    explicit SyntaxTrivia(SyntaxKind syntaxKind) noexcept;

    explicit SyntaxTrivia(SyntaxKind syntaxKind,
                          std::string_view text,
                          pg_size position = 0) noexcept;

    virtual ~SyntaxTrivia() noexcept;
    SyntaxTrivia(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia(SyntaxTrivia&&) noexcept = default;
    SyntaxTrivia& operator=(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia& operator=(SyntaxTrivia&&) noexcept = default;
    inline SyntaxKind syntaxKind() const noexcept { return _syntaxKind; }
    inline void setSyntaxKind(SyntaxKind syntaxKind) noexcept { _syntaxKind = syntaxKind; }
    inline pg_size position() const noexcept { return _position; }
    inline void setPosition(const pg_size position) noexcept { _position = position; }
    virtual inline std::string_view text() const noexcept { return _text; }
    inline virtual void setText(std::string_view text) noexcept { _text = text; }
    inline virtual bool isStructuredTrivia() const noexcept { return false; }
    inline virtual bool isDirective() const noexcept { return false; }
    inline virtual bool isSkippedTokensTrivia() const noexcept { return false; }
    inline virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept { return std::move(stack); }

protected:
    SyntaxKind _syntaxKind;
    pg_size _position;
    std::string_view _text;
    SyntaxToken* _pParent;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
