#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"

namespace polyglot::CodeAnalysis
{

LanguageSyntaxList::LanguageSyntaxList(std::vector<LanguageSyntaxNode*>&& children) noexcept
    : LanguageSyntaxNode{},
      _children{std::move(children)}
{}

LanguageSyntaxList::~LanguageSyntaxList() noexcept
{}

} // end namespace polyglot::CodeAnalysis
