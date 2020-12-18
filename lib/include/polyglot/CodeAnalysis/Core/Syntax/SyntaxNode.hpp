#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNodeFlags.hpp"

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
    inline SyntaxKind syntaxKind() const noexcept { return _syntaxKind; }
    inline void setSyntaxKind(SyntaxKind syntaxKind) noexcept { _syntaxKind = syntaxKind; }
    inline pg_size position() const noexcept { return _position; }
    inline void setPosition(const pg_size position) noexcept { _position = position; }
    inline bool containsDirectives() const noexcept { return (_flags & SyntaxNodeFlags::ContainsDirectives) != SyntaxNodeFlags::None; }
    inline virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept { return std::move(stack); }

protected:
    explicit SyntaxNode(SyntaxKind syntaxKind) noexcept;

    explicit SyntaxNode(SyntaxKind syntaxKind,
                        pg_size position) noexcept;

protected:
    SyntaxKind _syntaxKind;
    pg_size _position;
    SyntaxNodeFlags _flags;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
