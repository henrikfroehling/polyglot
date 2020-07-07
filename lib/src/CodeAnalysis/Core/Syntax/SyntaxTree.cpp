#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree(SourceText sourceText) noexcept
    : _sourceText{std::move(sourceText)}
{}

} // end namespace polyglot::CodeAnalysis
