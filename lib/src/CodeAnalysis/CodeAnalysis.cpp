#include "polyglot/CodeAnalysis/CodeAnalysis.hpp"
#include "CodeAnalysis/Core/Text/SourceText.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

SharedPtr<ISyntaxTree> parseSourceText(std::string filename,
                                       std::string source) noexcept
{
    SharedPtr<SourceText> ptrSourceText = std::make_shared<SourceText>(std::move(filename), std::move(source));
    ptrSourceText->parseLineStarts();
    return DelphiSyntaxTree::parseSourceText(std::move(ptrSourceText));
}

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis
