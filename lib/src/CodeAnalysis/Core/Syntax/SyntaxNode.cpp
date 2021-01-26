#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode() noexcept
    : ISyntaxNode{},
      _pUnderlyingNode{nullptr},
      _pParent{nullptr}
{}

SyntaxNode::SyntaxNode(LanguageSyntaxNode* underlyingNode,
                       ISyntaxNode* parent) noexcept
    : ISyntaxNode{},
      _pUnderlyingNode{underlyingNode},
      _pParent{parent}
{}

SyntaxNode::~SyntaxNode() noexcept
{}

TextSpan SyntaxNode::span() const noexcept
{
    pg_size start = _pUnderlyingNode->position();
    pg_size width = _pUnderlyingNode->fullWidth();
    pg_size leadingTriviaWidth = _pUnderlyingNode->leadingTriviaWidth();
    start += leadingTriviaWidth;
    width -= leadingTriviaWidth;
    width -= _pUnderlyingNode->trailingTriviaWidth();
    return TextSpan{start, width};
}

} // end namespace polyglot::CodeAnalysis
