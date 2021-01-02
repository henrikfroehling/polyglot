#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H

#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/DirectiveStack.hpp"
#include "CodeAnalysis/Core/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxNode
{
public:
    SyntaxNode() noexcept;
    virtual ~SyntaxNode() noexcept;
    SyntaxNode(const SyntaxNode&) noexcept = default;
    SyntaxNode(SyntaxNode&&) noexcept = default;
    SyntaxNode& operator=(const SyntaxNode&) noexcept = default;
    SyntaxNode& operator=(SyntaxNode&&) noexcept = default;
    inline virtual bool isToken() const noexcept { return false; }
    inline virtual bool isTrivia() const noexcept { return false; }
    inline virtual bool isStructuredTrivia() const noexcept { return false; }
    inline virtual bool isDirective() const noexcept { return false; }
    inline virtual bool isSkippedTokensTrivia() const noexcept { return false; }
    inline virtual bool isExpression() const noexcept { return false; }
    inline SyntaxKind syntaxKind() const noexcept { return _syntaxKind; }
    inline void setSyntaxKind(SyntaxKind syntaxKind) noexcept { _syntaxKind = syntaxKind; }
    inline pg_size position() const noexcept { return _position; }
    inline void setPosition(const pg_size position) noexcept { _position = position; }
    inline bool containsDirectives() const noexcept { return (_flags & SyntaxNodeFlags::ContainsDirectives) != SyntaxNodeFlags::None; }
    inline virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept { return std::move(stack); }
    virtual inline std::string_view text() const noexcept { return ""; }
    inline virtual void setText(std::string_view text) noexcept {}
    void setLeadingTrivia(std::vector<SyntaxNode*>&& leadingTrivia) noexcept;
    void setTrailingTrivia(std::vector<SyntaxNode*>&& trailingTrivia) noexcept;
    void addLeadingTrivia(SyntaxNode* leadingTrivia) noexcept;
    inline bool hasLeadingTrivia() const noexcept { return _leadingTrivia.size() > 0; }
    inline bool hasTrailingTrivia() const noexcept { return _trailingTrivia.size() > 0; }
    TextSpan span() const noexcept;
    inline TextSpan fullSpan() const noexcept { return TextSpan{_position, _fullWidth}; }
    inline pg_size width() const noexcept { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept { return _fullWidth; }
    inline pg_size endPosition() const noexcept { return _position + _fullWidth; }
    pg_size leadingTriviaWidth() const noexcept;
    pg_size trailingTriviaWidth() const noexcept;
    inline virtual pg_size childCount() const noexcept { return 0; }
    inline virtual SyntaxNode* child(pg_size index) const noexcept { return nullptr; }
    inline SyntaxNode* parent() const noexcept { return _pParent; }

protected:
    explicit SyntaxNode(SyntaxKind syntaxKind) noexcept;

    explicit SyntaxNode(SyntaxKind syntaxKind,
                        pg_size position) noexcept;

protected:
    SyntaxKind _syntaxKind;
    pg_size _position;
    SyntaxNodeFlags _flags;
    std::vector<SyntaxNode*> _leadingTrivia;
    std::vector<SyntaxNode*> _trailingTrivia;
    pg_size _fullWidth;
    SyntaxNode* _pParent;

private:
    SyntaxNode* firstTerminal() const noexcept;
    SyntaxNode* lastTerminal() const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
