#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIA_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;

class POLYGLOT_API ISyntaxTrivia : public ISyntaxNode
{
public:
    ISyntaxTrivia() noexcept = default;
    virtual ~ISyntaxTrivia() noexcept = default;

    ISyntaxTrivia(const ISyntaxTrivia&) noexcept = default;
    ISyntaxTrivia(ISyntaxTrivia&&) noexcept = default;
    ISyntaxTrivia& operator=(const ISyntaxTrivia&) noexcept = default;
    ISyntaxTrivia& operator=(ISyntaxTrivia&&) noexcept = default;

    virtual ISyntaxToken* token() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTRIVIA_H
