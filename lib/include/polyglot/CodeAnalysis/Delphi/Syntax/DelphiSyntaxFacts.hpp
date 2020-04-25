#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis::DelphiSyntaxFacts
{

bool POLYGLOT_API isPunctuation(SyntaxKind syntaxKind) noexcept;
bool POLYGLOT_API isCompoundPunctuation(SyntaxKind syntaxKind) noexcept;
bool POLYGLOT_API isKeyword(SyntaxKind syntaxKind) noexcept;
SyntaxKind POLYGLOT_API keywordKind(const std::string& text) noexcept;
std::string POLYGLOT_API syntaxKindName(SyntaxKind syntaxKind) noexcept;

} // end namespace polyglot::CodeAnalysis::DelphiSyntaxFacts

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
