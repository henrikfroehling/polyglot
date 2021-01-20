#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxNode
{
public:
    SyntaxNode() noexcept;
    virtual ~SyntaxNode() noexcept;
    SyntaxNode(const SyntaxNode&) noexcept = default;
    SyntaxNode(SyntaxNode&&) noexcept = default;
    SyntaxNode& operator=(const SyntaxNode&) noexcept = default;
    SyntaxNode& operator=(SyntaxNode&&) noexcept = default;
    inline virtual bool isExpression() const noexcept { return false; }
    inline SyntaxKind syntaxKind() const noexcept { return _syntaxKind; }
    inline void setSyntaxKind(SyntaxKind syntaxKind) noexcept { _syntaxKind = syntaxKind; }
    inline pg_size position() const noexcept { return _position; }
    inline void setPosition(const pg_size position) noexcept { _position = position; }
    inline bool containsDirectives() const noexcept { return (_flags & SyntaxNodeFlags::ContainsDirectives) != SyntaxNodeFlags::None; }
    virtual inline std::string_view text() const noexcept { return ""; }
    inline virtual void setText(std::string_view text) noexcept {}
    TextSpan span() const noexcept;
    inline TextSpan fullSpan() const noexcept { return TextSpan{_position, _fullWidth}; }
    inline pg_size width() const noexcept { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept { return _fullWidth; }
    inline pg_size endPosition() const noexcept { return _position + _fullWidth; }
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
    pg_size _fullWidth;
    SyntaxNode* _pParent;

private:
    pg_size leadingTriviaWidth() const noexcept;
    pg_size trailingTriviaWidth() const noexcept;

private:
    SyntaxNode* firstTerminal() const noexcept;
    SyntaxNode* lastTerminal() const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
