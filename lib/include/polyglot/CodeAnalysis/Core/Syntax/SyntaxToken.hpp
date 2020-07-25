#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <memory>
#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
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

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;
    inline bool isToken() const noexcept override { return true; }
    inline std::string_view text() const noexcept { return _text; }
    inline void setText(std::string_view text) noexcept { _text = text; }
    void addLeadingTrivia(std::shared_ptr<SyntaxTrivia> leadingTrivia) noexcept;
    void addTrailingTrivia(std::shared_ptr<SyntaxTrivia> trailingTrivia) noexcept;

private:
    std::string_view _text;
    std::vector<std::shared_ptr<SyntaxTrivia>> _leadingTrivia;
    std::vector<std::shared_ptr<SyntaxTrivia>> _trailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
