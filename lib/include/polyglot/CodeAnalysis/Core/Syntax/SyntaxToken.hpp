#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxNode;
class SyntaxTrivia;

class POLYGLOT_API SyntaxToken
{
public:
    SyntaxToken() noexcept;

    explicit SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text = "",
                         pg_size position = 0) noexcept;

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;
    inline SyntaxKind syntaxKind() const noexcept { return _syntaxKind; }
    inline void setSyntaxKind(SyntaxKind syntaxKind) noexcept { _syntaxKind = syntaxKind; }
    inline pg_size position() const noexcept { return _position; }
    inline void setPosition(const pg_size position) noexcept { _position = position; }
    virtual inline std::string_view text() const noexcept { return _text; }
    inline virtual void setText(std::string_view text) noexcept { _text = text; }
    void setLeadingTrivia(std::vector<SyntaxTrivia*>&& leadingTrivia) noexcept;
    void setTrailingTrivia(std::vector<SyntaxTrivia*>&& trailingTrivia) noexcept;
    void addLeadingTrivia(SyntaxTrivia* leadingTrivia) noexcept;
    inline bool hasLeadingTrivia() const noexcept { return _leadingTrivia.size() > 0; }
    inline bool hasTrailingTrivia() const noexcept { return _trailingTrivia.size() > 0; }
    virtual bool value() const noexcept; // TODO use variant / any as return type

protected:
    SyntaxKind _syntaxKind;
    pg_size _position;
    std::string_view _text;
    std::vector<SyntaxTrivia*> _leadingTrivia;
    std::vector<SyntaxTrivia*> _trailingTrivia;
    pg_size _fullWidth;
    SyntaxNode* _pParent;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
