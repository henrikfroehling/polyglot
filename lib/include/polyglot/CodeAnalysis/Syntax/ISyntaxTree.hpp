#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_SYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_SYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "../src/CodeAnalysis/Core/Syntax/SyntaxPool.hpp"
#include "../src/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;

class POLYGLOT_API ISyntaxTree
{
public:
    ISyntaxTree() noexcept;
    virtual ~ISyntaxTree() noexcept = default;
    inline LanguageSyntaxNode* root() const noexcept { return _pRoot; }

protected:
    explicit ISyntaxTree(SharedPtr<SourceText> sourceText,
                         LanguageSyntaxNode* root,
                         SyntaxPool&& syntaxPool) noexcept;

protected:
    SharedPtr<SourceText> _ptrSourceText;
    LanguageSyntaxNode* _pRoot;
    SyntaxPool _syntaxPool;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_SYNTAXTREE_H
