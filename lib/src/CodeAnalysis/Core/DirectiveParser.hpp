#ifndef POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H

#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/Lexer.hpp"
#include "CodeAnalysis/Core/Parser.hpp"

namespace polyglot::CodeAnalysis
{

class DirectiveStack;
class SyntaxTrivia;

class DirectiveParser : public Parser
{
public:
    DirectiveParser() = delete;
    virtual ~DirectiveParser() noexcept = default;

    virtual SyntaxTrivia* parseDirective(bool isActive,
                                         bool endIsActive,
                                         bool isFirstAfterTokenInFile,
                                         bool isAfterNonWhitespaceOnLine) noexcept = 0;

protected:
    explicit DirectiveParser(SharedPtr<Lexer> lexer,
                             const DirectiveStack& context) noexcept;

protected:
    const DirectiveStack& _context;

private:
    inline SyntaxNode* parseRoot() noexcept override { return nullptr; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
