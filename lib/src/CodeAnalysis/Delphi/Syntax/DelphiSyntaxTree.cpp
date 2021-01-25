#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Delphi/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                                   SyntaxNode* root,
                                   SyntaxPool&& syntaxPool) noexcept
    : SyntaxTree{std::move(sourceText), root, std::move(syntaxPool)}
{}

SharedPtr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SharedPtr<SourceText> sourceText) noexcept
{
    SyntaxPool syntaxPool{};
    DelphiParser parser{sourceText, syntaxPool};
    SyntaxNode* pSyntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), pSyntaxTreeRoot, std::move(syntaxPool));
}

} // end namespace polyglot::CodeAnalysis
