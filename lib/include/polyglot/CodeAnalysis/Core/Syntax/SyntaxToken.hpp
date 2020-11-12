#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <memory>
#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxToken : public SyntaxNode
{
public:
    SyntaxToken() noexcept;
    explicit SyntaxToken(SyntaxKind syntaxKind) noexcept;

    SyntaxToken(SyntaxKind syntaxKind,
                std::string_view text = "") noexcept;

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;
    inline bool isToken() const noexcept override { return true; }
    virtual inline std::string_view text() const noexcept { return _text; }
    inline virtual void setText(std::string_view text) noexcept { _text = text; }
    void setLeadingTrivia(std::vector<SyntaxNodePtr>&& leadingTrivia) noexcept;
    void setTrailingTrivia(std::vector<SyntaxNodePtr>&& trailingTrivia) noexcept;
    inline bool hasLeadingTrivia() const noexcept { return _leadingTrivia.size() > 0; }
    inline bool hasTrailingTrivia() const noexcept { return _trailingTrivia.size() > 0; }
    inline SyntaxKind contextualKind() const noexcept { return _contextualKind; }
    inline void setContextualKind(SyntaxKind contextualKind) noexcept { _contextualKind = contextualKind; }

protected:
    std::string_view _text;
    std::vector<SyntaxNodePtr> _leadingTrivia;
    std::vector<SyntaxNodePtr> _trailingTrivia;
    SyntaxKind _contextualKind;
};

using SyntaxTokenPtr = std::shared_ptr<SyntaxToken>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
