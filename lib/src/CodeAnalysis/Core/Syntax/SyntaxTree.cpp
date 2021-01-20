#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree() noexcept
    : _ptrSourceText{nullptr},
      _pRoot{nullptr}
{}

SyntaxTree::SyntaxTree(SharedPtr<SourceText> sourceText,
                       SyntaxNode* root) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _pRoot{root}
{}

} // end namespace polyglot::CodeAnalysis
