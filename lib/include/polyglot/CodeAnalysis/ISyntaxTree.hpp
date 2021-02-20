#ifndef POLYGLOT_CODEANALYSIS_SYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_SYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "../src/CodeAnalysis/Core/SyntaxPool.hpp"
#include "../src/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;

class POLYGLOT_API ISyntaxTree
{
public:
    ISyntaxTree() noexcept;
    virtual ~ISyntaxTree() noexcept = default;
    inline ISyntaxNode* root() const noexcept { return _pRoot; }

protected:
    explicit ISyntaxTree(SharedPtr<SourceText> sourceText,
                         ISyntaxNode* root,
                         SyntaxPool&& syntaxPool) noexcept;

protected:
    SharedPtr<SourceText> _ptrSourceText;
    ISyntaxNode* _pRoot;
    SyntaxPool _syntaxPool;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAXTREE_H
