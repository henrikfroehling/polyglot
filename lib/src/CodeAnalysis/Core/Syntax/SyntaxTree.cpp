#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree(SourceTextPtr sourceText,
                       SyntaxNodePtr root) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _ptrRoot{std::move(root)}
{}

} // end namespace polyglot::CodeAnalysis
