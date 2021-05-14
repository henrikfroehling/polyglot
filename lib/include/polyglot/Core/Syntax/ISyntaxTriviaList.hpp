#ifndef POLYGLOT_CORE_SYNTAX_ISYNTAXTRIVIALIST_H
#define POLYGLOT_CORE_SYNTAX_ISYNTAXTRIVIALIST_H

#include <string>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class ISyntaxTrivia;

class POLYGLOT_API ISyntaxTriviaList
{
public:
    virtual ~ISyntaxTriviaList() noexcept {}

    virtual ISyntaxToken* token() const noexcept = 0;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual std::string_view text() const noexcept = 0;

    virtual pg_size width() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual Text::TextSpan span() const noexcept = 0;

    virtual pg_size count() const noexcept = 0;
    virtual ISyntaxTrivia* child(pg_size index) const = 0;
    virtual ISyntaxTrivia* first() const noexcept = 0;
    virtual ISyntaxTrivia* last() const noexcept = 0;

    virtual std::string toString() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_ISYNTAXTRIVIALIST_H
