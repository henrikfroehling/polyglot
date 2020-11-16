#ifndef POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxFacts.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DirectiveParser : public Parser
{
public:
    DirectiveParser() = delete;
    virtual ~DirectiveParser() noexcept = default;

    virtual SyntaxNodePtr parseDirective(bool isActive,
                                         bool endIsActive,
                                         bool isFirstAfterTokenInFile,
                                         bool isAfterNonWhitespaceOnLine) noexcept = 0;

protected:
    explicit DirectiveParser(std::shared_ptr<Lexer> lexer,
                             const DirectiveStack& context,
                             std::shared_ptr<SyntaxFacts> syntaxFacts) noexcept;

protected:
    const DirectiveStack& _context;
    std::shared_ptr<SyntaxFacts> _ptrSyntaxFacts;

private:
    inline SyntaxNodePtr parseRoot() noexcept override { return nullptr; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
