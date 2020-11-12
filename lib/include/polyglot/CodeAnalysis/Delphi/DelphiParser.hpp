#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SourceTextPtr sourceText) noexcept;

private:
    std::shared_ptr<DelphiSyntaxFacts> _ptrSyntaxFacts;

private:
    SyntaxNodePtr parseRoot() noexcept override;
    DelphiCompilationUnitSyntaxPtr parseCompilationUnit() noexcept;
    DelphiUnitModuleSyntaxPtr parseUnitModule() noexcept;
    DelphiUnitHeadingSyntaxPtr parseUnitHeading() noexcept;
    DelphiUnitInterfaceSectionSyntaxPtr parseUnitInterfaceSection() noexcept;
    DelphiUnitImplementationSectionSyntaxPtr parseUnitImplementationSection() noexcept;
    DelphiUnitInitializationSectionSyntaxPtr parseUnitInitializationSection() noexcept;
    DelphiUnitFinalizationSectionSyntaxPtr parseUnitFinalizationSection() noexcept;
    DelphiPackageModuleSyntaxPtr parsePackageModule() noexcept;
    DelphiProgramModuleSyntaxPtr parseProgramModule() noexcept;
    DelphiUsesClauseSyntaxPtr parseUsesClause() noexcept;
    DelphiUnitReferenceDeclarationSyntaxPtr parseUnitReference() noexcept;
    NameExpressionSyntaxPtr parseQualifiedName() noexcept;

    NameExpressionSyntaxPtr parseQualifiedNameRight(NameExpressionSyntaxPtr left,
                                                    SyntaxTokenPtr dotToken) noexcept;

    IdentifierNameExpressionSyntaxPtr parseIdentifierName() noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
