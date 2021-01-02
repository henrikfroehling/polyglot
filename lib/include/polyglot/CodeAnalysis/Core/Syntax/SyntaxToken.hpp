#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxToken : public SyntaxNode
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
    inline bool isToken() const noexcept override { return true; }
    virtual inline std::string_view text() const noexcept override { return _text; }
    inline virtual void setText(std::string_view text) noexcept override { _text = text; }
    virtual bool value() const noexcept; // TODO use variant / any as return type

protected:
    std::string_view _text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
