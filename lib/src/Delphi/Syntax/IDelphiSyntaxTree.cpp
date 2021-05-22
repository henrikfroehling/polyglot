#include "polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp"
#include "polyglot/Core/Text/SourceText.hpp"
#include "Delphi/Syntax/DelphiSyntaxTree.hpp"

namespace polyglot::Delphi::Syntax
{

SharedPtr<IDelphiSyntaxTree> IDelphiSyntaxTree::parseSourceText(pg_string filename,
                                                                pg_string source) noexcept
{
    SharedPtr<Core::Text::SourceText> ptrSourceText = std::make_unique<Core::Text::SourceText>(std::move(filename), std::move(source));
    ptrSourceText->parseLineStarts();
    return DelphiSyntaxTree::parseSourceText(std::move(ptrSourceText));
}

} // end namespace polyglot::Delphi::Syntax
