#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTree::SyntaxTree(std::string sourceText) noexcept
    : _sourceText{std::move(sourceText)}
{}

} // end namespace polyglot::CodeAnalysis
