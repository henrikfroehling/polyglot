#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxTree
{
public:
    SyntaxTree() noexcept;
    virtual ~SyntaxTree() noexcept = default;
    inline const Ptr<SyntaxNode> root() const noexcept { return _ptrRoot; }

protected:
    explicit SyntaxTree(SharedPtr<SourceText> sourceText,
                        Ptr<SyntaxNode> root) noexcept;

protected:
    SharedPtr<SourceText> _ptrSourceText;
    Ptr<SyntaxNode> _ptrRoot;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
