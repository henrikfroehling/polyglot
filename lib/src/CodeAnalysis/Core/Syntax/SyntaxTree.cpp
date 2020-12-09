#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree() noexcept
    : _ptrSourceText{nullptr},
      _ptrRoot{nullptr}
{}

SyntaxTree::SyntaxTree(SharedPtr<SourceText> sourceText,
                       SyntaxNode* root) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _ptrRoot{root}
{}

} // end namespace polyglot::CodeAnalysis
