#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTrivia.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "../Parser/DirectiveStack.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;

class SyntaxTrivia : public SyntaxNode, public virtual ISyntaxTrivia
{
public:
    SyntaxTrivia() noexcept;

    explicit SyntaxTrivia(SyntaxKind syntaxKind,
                          std::string_view text,
                          pg_size position = 0,
                          pg_size fullWidth = 0,
                          ISyntaxToken* token = nullptr) noexcept;

    virtual ~SyntaxTrivia() noexcept;

    SyntaxTrivia(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia(SyntaxTrivia&&) noexcept = default;
    SyntaxTrivia& operator=(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia& operator=(SyntaxTrivia&&) noexcept = default;

    inline virtual pg_size width() const noexcept override final { return _fullWidth; }
    virtual ISyntaxNode* child(pg_size index) const override;
    inline std::string_view text() const noexcept override { return _text; }
    inline bool isTrivia() const noexcept override final { return true; }
    inline bool hasMissingTokens() const noexcept override final { return false; }
    inline ISyntaxToken* token() const noexcept override final { return _pToken; }

    inline bool hasLeadingTrivia() const noexcept override final { return false; }
    inline bool hasTrailingTrivia() const noexcept override final { return false; }
    inline pg_size leadingTriviaWidth() const noexcept override final { return 0; }
    inline pg_size trailingTriviaWidth() const noexcept override final { return 0; }

    inline virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept { return std::move(stack); }

protected:
    std::string_view _text;
    ISyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
