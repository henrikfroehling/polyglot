#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTOKEN_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ISyntaxToken : public virtual ISyntaxNode
{
public:
    virtual ~ISyntaxToken() noexcept {}

    virtual bool booleanValue() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXTOKEN_H
