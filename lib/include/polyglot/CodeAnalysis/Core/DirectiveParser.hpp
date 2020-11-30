#ifndef POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
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

    virtual SharedPtr<SyntaxNode> parseDirective(bool isActive,
                                                 bool endIsActive,
                                                 bool isFirstAfterTokenInFile,
                                                 bool isAfterNonWhitespaceOnLine) noexcept = 0;

protected:
    explicit DirectiveParser(SharedPtr<Lexer> lexer,
                             const DirectiveStack& context,
                             SharedPtr<SyntaxFacts> syntaxFacts) noexcept;

protected:
    const DirectiveStack& _context;
    SharedPtr<SyntaxFacts> _ptrSyntaxFacts;

private:
    inline SharedPtr<SyntaxNode> parseRoot() noexcept override { return nullptr; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
