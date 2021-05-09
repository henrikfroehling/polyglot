#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXLIST_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXLIST_H

#include <vector>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
#include "polyglot/Core/Types.hpp"
#include "SyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxList : public SyntaxNode, public virtual ISyntaxList
{
public:
    explicit SyntaxList(SyntaxKind syntaxKind,
                        std::vector<SyntaxNodeOrToken>&& children) noexcept;

    virtual ~SyntaxList() noexcept {}

    SyntaxList(const SyntaxList&) noexcept = default;
    SyntaxList(SyntaxList&&) noexcept = default;
    SyntaxList& operator=(const SyntaxList&) noexcept = default;
    SyntaxList& operator=(SyntaxList&&) noexcept = default;

    inline virtual pg_size childCount() const noexcept override { return _children.size(); }
    inline virtual SyntaxNodeOrToken child(pg_size index) const override { return _children[index]; }

    inline virtual SyntaxNodeOrToken first() const noexcept override { return _children.size() > 0 ? _children[0] : SyntaxNodeOrToken::empty(); }
    inline virtual SyntaxNodeOrToken last() const noexcept override { return _children.size() > 0 ? _children.back() : SyntaxNodeOrToken::empty(); }

protected:
    std::vector<SyntaxNodeOrToken> _children;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXLIST_H
