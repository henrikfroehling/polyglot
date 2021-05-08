#include "DelphiSyntaxTree.hpp"
#include "Core/Syntax/SyntaxPool.hpp"
#include "Delphi/Parser/DelphiParser.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxTree::DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                                   ISyntaxNode* root,
                                   SyntaxPool&& syntaxPool) noexcept
    : ISyntaxTree{std::move(sourceText), root, std::move(syntaxPool)}
{}

SharedPtr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SharedPtr<SourceText> sourceText) noexcept
{
    DelphiParser parser{sourceText};
    ISyntaxNode* pSyntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), pSyntaxTreeRoot, parser.takeSyntaxPool());
}

} // end namespace polyglot::Delphi::Syntax
