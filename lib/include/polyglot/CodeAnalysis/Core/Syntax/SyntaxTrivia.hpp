#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxTrivia : public SyntaxNode
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
    inline bool isTrivia() const noexcept override { return true; }
    virtual inline std::string_view text() const noexcept { return _text; }
    inline virtual void setText(std::string_view text) noexcept { _text = text; }

protected:
    std::string_view _text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
