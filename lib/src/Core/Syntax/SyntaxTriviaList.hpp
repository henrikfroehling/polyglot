#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIALIST_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIALIST_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxTriviaList : public ISyntaxTriviaList
{
public:
    explicit SyntaxTriviaList(std::vector<ISyntaxTrivia*>&& trivia,
                              ISyntaxToken* token = nullptr) noexcept;

    virtual ~SyntaxTriviaList() noexcept {}

    SyntaxTriviaList(const SyntaxTriviaList&) noexcept = default;
    SyntaxTriviaList(SyntaxTriviaList&&) noexcept = default;
    SyntaxTriviaList& operator=(const SyntaxTriviaList&) noexcept = default;
    SyntaxTriviaList& operator=(SyntaxTriviaList&&) noexcept = default;

    inline ISyntaxToken* token() const noexcept override final { return _pToken; }

    inline LanguageKind languageKind() const noexcept override final { return _pToken != nullptr ? _pToken->languageKind() : LanguageKind::Unknown; }
    inline std::string_view text() const noexcept override final { return std::string_view{}; }

    inline pg_size width() const noexcept override final { return _width; }
    inline pg_size position() const noexcept override final { return _position; }
    inline pg_size endPosition() const noexcept override final { return _position + _width; }
    inline Text::TextSpan span() const noexcept override final { return Text::TextSpan{_position, _width}; }

    inline pg_size count() const noexcept override final { return _children.size(); }
    inline ISyntaxTrivia* child(pg_size index) const override final { return _children[index]; }
    inline ISyntaxTrivia* first() const noexcept override final { return _children.size() > 0 ? _children[0] : nullptr; }
    inline ISyntaxTrivia* last() const noexcept override final { return _children.size() > 0 ? _children.back() : nullptr; }

protected:
    void adjustWidth(ISyntaxTrivia* trivia) noexcept;

protected:
    friend class SyntaxToken;

    pg_size _position;
    pg_size _width;
    std::vector<ISyntaxTrivia*> _children;
    ISyntaxToken* _pToken;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIALIST_H
