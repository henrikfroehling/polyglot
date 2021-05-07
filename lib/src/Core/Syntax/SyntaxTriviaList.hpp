#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIALIST_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIALIST_H

#include <string_view>
#include "polyglot/Core/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class ISyntaxTrivia;

class SyntaxTriviaList : public ISyntaxTriviaList
{
public:
    virtual ~SyntaxTriviaList() noexcept {}

    inline virtual ISyntaxToken* token() const noexcept override { return nullptr; }

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline virtual std::string_view text() const noexcept override { return std::string_view{}; }

    inline virtual pg_size width() const noexcept override { return 0; }
    inline virtual pg_size position() const noexcept override { return 0; }
    inline virtual pg_size endPosition() const noexcept override { return 0; }
    inline virtual pg_size spanStart() const noexcept override { return 0; }
    inline virtual TextSpan span() const noexcept override { return TextSpan{}; }

    inline virtual pg_size count() const override { return 0; }
    inline virtual ISyntaxTrivia* child(pg_size index) const override { return nullptr; }
    inline virtual ISyntaxTrivia* first() const override { return nullptr; }
    inline virtual ISyntaxTrivia* last() const override { return nullptr; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIALIST_H
