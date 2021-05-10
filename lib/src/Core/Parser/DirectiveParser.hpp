#ifndef POLYGLOT_CORE_PARSER_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CORE_PARSER_DELPHIDIRECTIVEPARSER_H

#include "polyglot/Core/Types.hpp"
#include "Core/Parser/Lexer.hpp"
#include "Core/Parser/Parser.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxTrivia;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Core::Parser
{

class DirectiveStack;

class DirectiveParser : public Parser
{
public:
    DirectiveParser() = delete;
    virtual ~DirectiveParser() noexcept {}

    virtual Syntax::ISyntaxTrivia* parseDirective(bool isActive,
                                                  bool endIsActive,
                                                  bool isFirstAfterTokenInFile,
                                                  bool isAfterNonWhitespaceOnLine) noexcept = 0;

protected:
    explicit DirectiveParser(SharedPtr<Lexer> lexer,
                             const DirectiveStack& context) noexcept;

protected:
    const DirectiveStack& _context;

private:
    inline Syntax::ISyntaxNode* parseRoot() noexcept override { return nullptr; }
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_DELPHIDIRECTIVEPARSER_H
