#include "polyglot/CodeAnalysis/ISyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

ISyntaxTree::ISyntaxTree() noexcept
    : _ptrSourceText{nullptr},
      _pRoot{nullptr},
      _syntaxPool{}
{}

ISyntaxTree::ISyntaxTree(SharedPtr<SourceText> sourceText,
                         ISyntaxNode* root,
                         SyntaxPool&& syntaxPool) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _pRoot{root},
      _syntaxPool{std::move(syntaxPool)}
{}

} // end namespace polyglot::CodeAnalysis
