#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H

#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxTree
{
public:
    SyntaxTree() noexcept = default;
    virtual ~SyntaxTree() noexcept = default;

protected:
    explicit SyntaxTree(SourceText sourceText) noexcept;

protected:
    SourceText _sourceText;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
