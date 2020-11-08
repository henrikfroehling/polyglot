#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H

#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiDirectiveParser : public Parser
{
public:
    DelphiDirectiveParser() = delete;
    explicit DelphiDirectiveParser(std::shared_ptr<Lexer> lexer,
                                   const DirectiveStack& context) noexcept;

    SyntaxNodePtr parseDirective(bool isActive,
                                 bool endIsActive,
                                 bool isFirstAfterTokenInFile,
                                 bool isAfterNonWhitespaceOnLine) noexcept;

private:
    inline SyntaxNodePtr parseRoot() noexcept override { return nullptr; }

    DelphiDirectiveTriviaSyntaxPtr parseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                    SyntaxTokenPtr keyword,
                                                    bool isActive) noexcept;

    DelphiDirectiveTriviaSyntaxPtr parseElseDirective(SyntaxTokenPtr openBraceDollarToken,
                                                      SyntaxTokenPtr keyword,
                                                      bool isActive,
                                                      bool endIsActive) noexcept;

    DelphiDirectiveTriviaSyntaxPtr parseElseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                        SyntaxTokenPtr keyword,
                                                        bool isActive,
                                                        bool endIsActive) noexcept;

    DelphiDirectiveTriviaSyntaxPtr parseEndIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                       SyntaxTokenPtr keyword,
                                                       bool isActive,
                                                       bool endIsActive) noexcept;

    DelphiDirectiveTriviaSyntaxPtr parseDefineOrUndefDirective(SyntaxTokenPtr openBraceDollarToken,
                                                               SyntaxTokenPtr keyword,
                                                               bool isActive,
                                                               bool isFollowingToken) noexcept;

    DelphiDirectiveTriviaSyntaxPtr parseRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                        SyntaxTokenPtr keyword,
                                                        bool isActive) noexcept;

    DelphiDirectiveTriviaSyntaxPtr parseEndRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                           SyntaxTokenPtr keyword,
                                                           bool isActive) noexcept;

    SyntaxTokenPtr parseEndOfDirective() noexcept;
    DelphiExpressionSyntaxPtr parseExpression() noexcept;
    DelphiExpressionSyntaxPtr parseLogicalOr() noexcept;
    DelphiExpressionSyntaxPtr parseLogicalAnd() noexcept;
    DelphiExpressionSyntaxPtr parseEquality() noexcept;
    DelphiExpressionSyntaxPtr parseLogicalNot() noexcept;
    DelphiExpressionSyntaxPtr parsePrimary() noexcept;
    bool evaluateBool(DelphiExpressionSyntaxPtr expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;

private:
    const DirectiveStack& _context;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
