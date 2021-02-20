#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_DELPHIDIRECTIVEPARSER_H

#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/Parser/Lexer.hpp"
#include "CodeAnalysis/Core/Parser/Parser.hpp"

namespace polyglot::CodeAnalysis
{

class DirectiveStack;
class ISyntaxNode;
class ISyntaxTrivia;

class DirectiveParser : public Parser
{
public:
    DirectiveParser() = delete;
    virtual ~DirectiveParser() noexcept = default;

    virtual ISyntaxTrivia* parseDirective(bool isActive,
                                          bool endIsActive,
                                          bool isFirstAfterTokenInFile,
                                          bool isAfterNonWhitespaceOnLine) noexcept = 0;

protected:
    explicit DirectiveParser(SharedPtr<Lexer> lexer,
                             const DirectiveStack& context) noexcept;

protected:
    const DirectiveStack& _context;

private:
    inline ISyntaxNode* parseRoot() noexcept override { return nullptr; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_DELPHIDIRECTIVEPARSER_H
