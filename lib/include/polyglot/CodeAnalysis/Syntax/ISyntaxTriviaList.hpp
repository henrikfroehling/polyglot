#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIALIST_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIALIST_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;
class ISyntaxTrivia;

class POLYGLOT_API ISyntaxTriviaList
{
public:
    virtual ~ISyntaxTriviaList() noexcept = default;

    virtual pg_size position() const noexcept = 0;
    virtual ISyntaxToken* token() const noexcept = 0;
    virtual pg_size count() const noexcept = 0;
    virtual ISyntaxTrivia* child(pg_size index) const noexcept = 0;
    virtual TextSpan span() const noexcept = 0;
    virtual TextSpan fullSpan() const noexcept = 0;
    virtual ISyntaxTrivia* first() const noexcept = 0;
    virtual ISyntaxTrivia* last() const noexcept = 0;

protected:
    ISyntaxTriviaList() noexcept = default;
    ISyntaxTriviaList(const ISyntaxTriviaList&) noexcept = default;
    ISyntaxTriviaList(ISyntaxTriviaList&&) noexcept = default;
    ISyntaxTriviaList& operator=(const ISyntaxTriviaList&) noexcept = default;
    ISyntaxTriviaList& operator=(ISyntaxTriviaList&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIALIST_H
