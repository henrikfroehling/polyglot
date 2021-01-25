#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree() noexcept
    : _ptrSourceText{nullptr},
      _pRoot{nullptr},
      _syntaxPool{}
{}

SyntaxTree::SyntaxTree(SharedPtr<SourceText> sourceText,
                       SyntaxNode* root,
                       SyntaxPool&& syntaxPool) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _pRoot{root},
      _syntaxPool{std::move(syntaxPool)}
{}

} // end namespace polyglot::CodeAnalysis
