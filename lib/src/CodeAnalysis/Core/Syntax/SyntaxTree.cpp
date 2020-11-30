#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree(SharedPtr<SourceText> sourceText,
                       SharedPtr<SyntaxNode> root) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _ptrRoot{std::move(root)}
{}

} // end namespace polyglot::CodeAnalysis
