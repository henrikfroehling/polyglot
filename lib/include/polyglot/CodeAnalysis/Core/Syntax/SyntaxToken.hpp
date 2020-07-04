#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

//#include <string>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxToken : public SyntaxNode
{
public:
    SyntaxToken() noexcept;
    explicit SyntaxToken(SyntaxKind syntaxKind) noexcept;

    SyntaxToken(SyntaxKind syntaxKind,
                pg_size position,
                std::string_view text = "") noexcept;

    inline bool isToken() const noexcept override { return true; }
    inline pg_size position() const noexcept { return _position; }
    inline void setPosition(pg_size position) noexcept { _position = position; }
    inline std::string_view text() const noexcept { return _text; }
    inline void setText(std::string_view text) noexcept { _text = text; }

private:
    pg_size _position;
    std::string_view _text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
