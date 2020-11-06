#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiDirectiveParser : public Parser
{
public:
    DelphiDirectiveParser() = delete;
    explicit DelphiDirectiveParser(std::shared_ptr<Lexer> lexer) noexcept;

    SyntaxNodePtr parseDirective(bool isActive,
                                 bool endIsActive,
                                 bool isFirstAfterTokenInFile,
                                 bool isAfterNonWhitespaceOnLine) noexcept;

private:
    inline SyntaxNodePtr parseRoot() noexcept override { return nullptr; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
