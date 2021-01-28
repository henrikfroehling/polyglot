#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"

namespace polyglot::CodeAnalysis
{

LanguageSyntaxList::LanguageSyntaxList(std::vector<LanguageSyntaxNode*>&& children) noexcept
    : LanguageSyntaxNode{},
      _children{std::move(children)}
{
    for (LanguageSyntaxNode* child : _children)
        adjustWidthAndFlags(child);
}

LanguageSyntaxList::~LanguageSyntaxList() noexcept
{}

} // end namespace polyglot::CodeAnalysis
