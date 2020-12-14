#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxToken : public SyntaxNode
{
public:
    SyntaxToken() noexcept;

    explicit SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text = "") noexcept;

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;
    inline bool isToken() const noexcept override { return true; }
    virtual inline std::string_view text() const noexcept { return _text; }
    inline virtual void setText(std::string_view text) noexcept { _text = text; }
    void setLeadingTrivia(std::vector<SyntaxNode*>&& leadingTrivia) noexcept;
    void setTrailingTrivia(std::vector<SyntaxNode*>&& trailingTrivia) noexcept;
    void addLeadingTrivia(SyntaxNode* leadingTrivia) noexcept;
    inline bool hasLeadingTrivia() const noexcept { return _leadingTrivia.size() > 0; }
    inline bool hasTrailingTrivia() const noexcept { return _trailingTrivia.size() > 0; }
    virtual bool value() const noexcept; // TODO use variant / any as return type

protected:
    std::string_view _text;
    std::vector<SyntaxNode*> _leadingTrivia;
    std::vector<SyntaxNode*> _trailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
