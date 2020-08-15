#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"

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

protected:
    explicit SyntaxNode(SyntaxKind syntaxKind) noexcept;

    explicit SyntaxNode(SyntaxKind syntaxKind,
                        pg_size position) noexcept;

protected:
    SyntaxKind _syntaxKind;
};

using SyntaxNodePtr = std::shared_ptr<SyntaxNode>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
