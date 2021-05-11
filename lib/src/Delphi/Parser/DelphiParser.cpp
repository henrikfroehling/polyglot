#include "Delphi/Parser/DelphiParser.hpp"
#include <cassert>
#include <iostream>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "Delphi/Parser/DelphiLexer.hpp"
#include "Delphi/Parser/DelphiSyntaxFacts.hpp"
#include "Delphi/Syntax/DelphiEndOfModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Parser
{

using namespace Core::Syntax;
using namespace Delphi::Syntax;

DelphiParser::DelphiParser(SharedPtr<Core::Text::SourceText> sourceText) noexcept
    : Core::Parser::Parser{std::make_shared<DelphiLexer>(sourceText)},
      _syntaxFactory{_ptrLexer->syntaxPool()}
{}

ISyntaxNode* DelphiParser::parseRoot() noexcept
{
    if (DelphiSyntaxFacts::isModuleStart(currentToken()->syntaxKind()))
        return parseCompilationUnit();
    else
    {
        // TODO parse different entry points
        return nullptr;
    }
}

DelphiCompilationUnitSyntax* DelphiParser::parseCompilationUnit() noexcept
{
    ISyntaxToken* pCurrentToken = currentToken();
    DelphiCompilationUnitSyntax* pCompilationUnit = nullptr;

    switch (pCurrentToken->syntaxKind())
    {
        case SyntaxKind::UnitKeyword:
            pCompilationUnit = parseUnitModule();
            break;
        case SyntaxKind::PackageKeyword:
            pCompilationUnit = parsePackageModule();
            break;
        case SyntaxKind::ProgramKeyword:
            pCompilationUnit = parseProgramModule();
            break;
        default:
        {
            ISyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);
            pCompilationUnit = DelphiCompilationUnitSyntax::create(_syntaxFactory, SyntaxKind::CompilationUnit, pEOFToken);
        }
    }

    assert(pCompilationUnit != nullptr);
    return pCompilationUnit;
}

DelphiUnitModuleSyntax* DelphiParser::parseUnitModule() noexcept
{
    DelphiUnitHeadSyntax* pHead = nullptr;
    DelphiUnitInterfaceSectionSyntax* pInterfaceSection = nullptr;
    DelphiUnitImplementationSectionSyntax* pImplementationSection = nullptr;
    DelphiUnitInitializationSectionSyntax* pInitializationSection = nullptr; // optional
    DelphiUnitFinalizationSectionSyntax* pFinalizationSection = nullptr; // optional, but requires initialization section

    while (true)
    {
        ISyntaxToken* pCurrentToken = currentToken();

        switch (pCurrentToken->syntaxKind())
        {
            case SyntaxKind::UnitKeyword:
                pHead = parseUnitHead();
                break;
            case SyntaxKind::InterfaceKeyword:
                pInterfaceSection = parseUnitInterfaceSection();
                break;
            case SyntaxKind::ImplementationKeyword:
                pImplementationSection = parseUnitImplementationSection();
                break;
            case SyntaxKind::InitializationKeyword:
                pInitializationSection = parseUnitInitializationSection();
                advance();
                break;
            case SyntaxKind::FinalizationKeyword:
                pFinalizationSection = parseUnitFinalizationSection();
                advance();
                break;
            case SyntaxKind::EndKeyword:
            {
                if (peekToken(2)->syntaxKind() == SyntaxKind::DotToken)
                    goto endOfUnit;

                break;
            }
            case SyntaxKind::EndOfFileToken:
                goto endOfUnit;
        }
    }

endOfUnit:
    DelphiEndOfModuleSyntax* endOfModule = parseEndOfModule();
    ISyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);

    return DelphiUnitModuleSyntax::create(_syntaxFactory, pHead, pInterfaceSection, pImplementationSection,
                                          endOfModule, pEOFToken, pInitializationSection, pFinalizationSection);
}

DelphiUnitHeadSyntax* DelphiParser::parseUnitHead() noexcept
{
    ISyntaxToken* pUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    NameExpressionSyntax* pName = parseQualifiedName();
    ISyntaxToken* pInKeyword{nullptr};
    ISyntaxToken* pFilename{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken();
        pFilename = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUnitHeadSyntax::create(_syntaxFactory, pUnitKeyword, pName, pSemiColonToken, pInKeyword, pFilename);
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    ISyntaxToken* pInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitInterfaceSectionSyntax::create(_syntaxFactory, pInterfaceKeyword, pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    ISyntaxToken* pImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitImplementationSectionSyntax::create(_syntaxFactory, pImplementationKeyword, pUses);
}

DelphiUnitInitializationSectionSyntax* DelphiParser::parseUnitInitializationSection() noexcept
{
    return DelphiUnitInitializationSectionSyntax::create(_syntaxFactory);
}

DelphiUnitFinalizationSectionSyntax* DelphiParser::parseUnitFinalizationSection() noexcept
{
    return DelphiUnitFinalizationSectionSyntax::create(_syntaxFactory);
}

DelphiPackageModuleSyntax* DelphiParser::parsePackageModule() noexcept
{
    return DelphiPackageModuleSyntax::create(_syntaxFactory);
}

DelphiProgramModuleSyntax* DelphiParser::parseProgramModule() noexcept
{
    return DelphiProgramModuleSyntax::create(_syntaxFactory);
}

DelphiUsesClauseSyntax* DelphiParser::parseUsesClause() noexcept
{
    ISyntaxToken* pUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<SyntaxVariant> unitReferences;

    DelphiUnitReferenceDeclarationSyntax* pUnitReference = parseUnitReference();
    unitReferences.push_back(SyntaxVariant::asNode(dynamic_cast<SyntaxNode*>(pUnitReference)));

    while (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        ISyntaxToken* pCommaToken = takeToken();
        pUnitReference = parseUnitReference();
        unitReferences.push_back(SyntaxVariant::asToken(pCommaToken));
        unitReferences.push_back(SyntaxVariant::asNode(dynamic_cast<SyntaxNode*>(pUnitReference)));
    }

    SyntaxList* pUnitReferences = dynamic_cast<SyntaxList*>(_syntaxFactory.syntaxList(SyntaxKind::UnitReferencesList, std::move(unitReferences)));
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUsesClauseSyntax::create(_syntaxFactory, pUsesKeyword, pUnitReferences, pSemiColonToken);
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    NameExpressionSyntax* pUnitName = parseQualifiedName();
    ISyntaxToken* pInKeyword{nullptr};
    ISyntaxToken* pSourceFile{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken(SyntaxKind::InKeyword);
        pSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    return DelphiUnitReferenceDeclarationSyntax::create(_syntaxFactory, pUnitName, pInKeyword, pSourceFile);
}

NameExpressionSyntax* DelphiParser::parseQualifiedName() noexcept
{
    NameExpressionSyntax* pName = parseIdentifierName();

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        ISyntaxToken* pSeparator = takeToken();
        pName = parseQualifiedNameRight(pName, pSeparator);
    }

    return pName;
}

NameExpressionSyntax* DelphiParser::parseQualifiedNameRight(NameExpressionSyntax* left,
                                                            ISyntaxToken* dotToken) noexcept
{
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    SimpleNameExpressionSyntax* pRight = parseIdentifierName();
    return QualifiedNameExpressionSyntax::create(_syntaxFactory, left, dotToken, pRight);
}

IdentifierNameExpressionSyntax* DelphiParser::parseIdentifierName() noexcept
{
    ISyntaxToken* pCurrentToken = currentToken();

    if (pCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        ISyntaxToken* pIdentifier = takeToken();
        return IdentifierNameExpressionSyntax::create(_syntaxFactory, pIdentifier);
    }
    else
    {
        ISyntaxToken* pMissingIdentifier = _syntaxFactory.missingToken(SyntaxKind::IdentifierToken, pCurrentToken->text(), pCurrentToken->position());
        return IdentifierNameExpressionSyntax::create(_syntaxFactory, pMissingIdentifier);
    }
}

DelphiEndOfModuleSyntax* DelphiParser::parseEndOfModule() noexcept
{
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    return DelphiEndOfModuleSyntax::create(_syntaxFactory, pEndKeyword, pDotToken);
}

} // end namespace polyglot::Delphi::Parser
