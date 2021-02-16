#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIALIST_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIALIST_H

#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;
class ISyntaxTrivia;

class SyntaxTriviaList : public SyntaxNode, public ISyntaxTriviaList
{
public:
    explicit SyntaxTriviaList(ISyntaxToken* token = nullptr) noexcept;
    virtual ~SyntaxTriviaList() noexcept;

    SyntaxTriviaList(const SyntaxTriviaList&) noexcept = default;
    SyntaxTriviaList(SyntaxTriviaList&&) noexcept = default;
    SyntaxTriviaList& operator=(const SyntaxTriviaList&) noexcept = default;
    SyntaxTriviaList& operator=(SyntaxTriviaList&&) noexcept = default;

    inline pg_size childCount() const noexcept override { return _children.size(); }
    inline ISyntaxNode* child(pg_size index) const override { return _children[index]; }
    inline TextSpan span() const noexcept override final { return TextSpan{_position, _fullWidth}; }
    inline TextSpan fullSpan() const noexcept override final { return TextSpan{_position, _fullWidth}; }
    inline bool hasMissingTokens() const noexcept override final { return false; }
    ISyntaxToken* token() const noexcept override;
    inline ISyntaxTrivia* first() const noexcept override final { return _children.size() > 0 ? _children[0] : nullptr; }
    inline ISyntaxTrivia* last() const noexcept override final { return _children.size() > 0 ? _children.back() : nullptr; }
    void add(ISyntaxTrivia* trivia) noexcept;

protected:
    std::vector<ISyntaxTrivia*> _children;
    ISyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIALIST_H
