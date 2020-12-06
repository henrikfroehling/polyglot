#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree() noexcept
    : _ptrSourceText{nullptr},
      _ptrRoot{nullptr}
{}

SyntaxTree::SyntaxTree(SharedPtr<SourceText> sourceText,
                       Ptr<SyntaxNode> root) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _ptrRoot{root}
{}

} // end namespace polyglot::CodeAnalysis
