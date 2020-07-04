#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis::DelphiSyntaxFacts
{

bool POLYGLOT_API isPunctuation(SyntaxKind syntaxKind) noexcept;
bool POLYGLOT_API isCompoundPunctuation(SyntaxKind syntaxKind) noexcept;
bool POLYGLOT_API isKeyword(SyntaxKind syntaxKind) noexcept;
SyntaxKind POLYGLOT_API keywordKind(std::string_view text) noexcept;

} // end namespace polyglot::CodeAnalysis::DelphiSyntaxFacts

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
