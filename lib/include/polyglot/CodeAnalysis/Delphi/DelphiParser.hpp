#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiCompilationUnitSyntax;
class DelphiPackageModuleSyntax;
class DelphiProgramModuleSyntax;
class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadingSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class DelphiUnitModuleSyntax;
class DelphiUnitReferenceDeclarationSyntax;
class DelphiUsesClauseSyntax;
class IdentifierNameExpressionSyntax;
class NameExpressionSyntax;
class SyntaxNode;
class SyntaxToken;

class POLYGLOT_API DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SharedPtr<SourceText> sourceText) noexcept;

private:
    SharedPtr<DelphiSyntaxFacts> _ptrSyntaxFacts;

private:
    SyntaxNode* parseRoot() noexcept override;
    DelphiCompilationUnitSyntax* parseCompilationUnit() noexcept;
    DelphiUnitModuleSyntax* parseUnitModule() noexcept;
    DelphiUnitHeadingSyntax* parseUnitHeading() noexcept;
    DelphiUnitInterfaceSectionSyntax* parseUnitInterfaceSection() noexcept;
    DelphiUnitImplementationSectionSyntax* parseUnitImplementationSection() noexcept;
    DelphiUnitInitializationSectionSyntax* parseUnitInitializationSection() noexcept;
    DelphiUnitFinalizationSectionSyntax* parseUnitFinalizationSection() noexcept;
    DelphiPackageModuleSyntax* parsePackageModule() noexcept;
    DelphiProgramModuleSyntax* parseProgramModule() noexcept;
    DelphiUsesClauseSyntax* parseUsesClause() noexcept;
    DelphiUnitReferenceDeclarationSyntax* parseUnitReference() noexcept;
    NameExpressionSyntax* parseQualifiedName() noexcept;

    NameExpressionSyntax* parseQualifiedNameRight(NameExpressionSyntax* left,
                                                  SyntaxToken* dotToken) noexcept;

    IdentifierNameExpressionSyntax* parseIdentifierName() noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
