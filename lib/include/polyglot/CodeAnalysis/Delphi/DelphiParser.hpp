#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

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
    explicit DelphiParser(SharedPtr<SourceText> sourceText) noexcept;

private:
    SharedPtr<DelphiSyntaxFacts> _ptrSyntaxFacts;

private:
    Ptr<SyntaxNode> parseRoot() noexcept override;
    Ptr<DelphiCompilationUnitSyntax> parseCompilationUnit() noexcept;
    Ptr<DelphiUnitModuleSyntax> parseUnitModule() noexcept;
    Ptr<DelphiUnitHeadingSyntax> parseUnitHeading() noexcept;
    Ptr<DelphiUnitInterfaceSectionSyntax> parseUnitInterfaceSection() noexcept;
    Ptr<DelphiUnitImplementationSectionSyntax> parseUnitImplementationSection() noexcept;
    Ptr<DelphiUnitInitializationSectionSyntax> parseUnitInitializationSection() noexcept;
    Ptr<DelphiUnitFinalizationSectionSyntax> parseUnitFinalizationSection() noexcept;
    Ptr<DelphiPackageModuleSyntax> parsePackageModule() noexcept;
    Ptr<DelphiProgramModuleSyntax> parseProgramModule() noexcept;
    Ptr<DelphiUsesClauseSyntax> parseUsesClause() noexcept;
    Ptr<DelphiUnitReferenceDeclarationSyntax> parseUnitReference() noexcept;
    Ptr<NameExpressionSyntax> parseQualifiedName() noexcept;

    Ptr<NameExpressionSyntax> parseQualifiedNameRight(Ptr<NameExpressionSyntax> left,
                                                      Ptr<SyntaxToken> dotToken) noexcept;

    Ptr<IdentifierNameExpressionSyntax> parseIdentifierName() noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
