#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxNode;

class POLYGLOT_API SyntaxTree
{
public:
    SyntaxTree() noexcept;
    virtual ~SyntaxTree() noexcept = default;
    inline SyntaxNode* root() const noexcept { return _ptrRoot; }

protected:
    explicit SyntaxTree(SharedPtr<SourceText> sourceText,
                        SyntaxNode* root) noexcept;

protected:
    SharedPtr<SourceText> _ptrSourceText;
    SyntaxNode* _ptrRoot;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTREE_H
