#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                                   SyntaxNode* root) noexcept
    : SyntaxTree{std::move(sourceText), root}
{}

SharedPtr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SharedPtr<SourceText> sourceText) noexcept
{
    DelphiParser parser{sourceText};
    SyntaxNode* syntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), syntaxTreeRoot);
}

} // end namespace polyglot::CodeAnalysis
