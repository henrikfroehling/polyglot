#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H

#include <string>
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxTree
{
public:
    SyntaxTree() = delete;
    virtual ~SyntaxTree() noexcept = default;

protected:
    explicit SyntaxTree(std::string sourceText) noexcept;

protected:
    std::string _sourceText;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
