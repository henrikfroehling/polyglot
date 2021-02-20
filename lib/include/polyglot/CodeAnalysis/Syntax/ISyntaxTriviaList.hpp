#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIALIST_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIALIST_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;
class ISyntaxTrivia;

class POLYGLOT_API ISyntaxTriviaList : public virtual ISyntaxNode
{
public:
    virtual ~ISyntaxTriviaList() noexcept {}

    virtual ISyntaxToken* token() const noexcept = 0;
    virtual ISyntaxTrivia* first() const = 0;
    virtual ISyntaxTrivia* last() const = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIALIST_H
