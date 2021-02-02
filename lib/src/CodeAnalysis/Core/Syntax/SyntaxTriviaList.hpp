#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIALIST_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIALIST_H

#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxTrivia;

class SyntaxTriviaList : public ISyntaxTriviaList
{
public:
    SyntaxTriviaList() = delete;

    explicit SyntaxTriviaList(LanguageSyntaxNode* underlyingNode,
                              ISyntaxToken* token = nullptr) noexcept;

    virtual ~SyntaxTriviaList() noexcept;

    SyntaxTriviaList(const SyntaxTriviaList&) noexcept = default;
    SyntaxTriviaList(SyntaxTriviaList&&) noexcept = default;
    SyntaxTriviaList& operator=(const SyntaxTriviaList&) noexcept = default;
    SyntaxTriviaList& operator=(SyntaxTriviaList&&) noexcept = default;

    inline pg_size position() const noexcept override { return _pToken != nullptr ? _pToken->position() : 0; }
    inline ISyntaxToken* token() const noexcept override { return _pToken; }
    inline pg_size count() const noexcept override { return _pUnderlyingNode->childCount(); }
    ISyntaxTrivia* child(pg_size index) const noexcept override;
    TextSpan span() const noexcept override;
    TextSpan fullSpan() const noexcept override;
    ISyntaxTrivia* first() const noexcept override;
    ISyntaxTrivia* last() const noexcept override;

protected:
    LanguageSyntaxNode* _pUnderlyingNode;
    ISyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIALIST_H
