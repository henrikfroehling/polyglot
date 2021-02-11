#include "CodeAnalysis/Delphi/Parser/DelphiParser.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "CodeAnalysis/Delphi/Parser/DelphiLexer.hpp"
#include "CodeAnalysis/Delphi/Parser/DelphiSyntaxFacts.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiEndOfModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include <cassert>
#include <iostream>

namespace polyglot::CodeAnalysis
{

DelphiParser::DelphiParser(SharedPtr<SourceText> sourceText) noexcept
    : Parser{std::make_shared<DelphiLexer>(sourceText)},
      _syntaxFactory{_ptrLexer->syntaxPool()}
{}

LanguageSyntaxNode* DelphiParser::parseRoot() noexcept
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
    LanguageSyntaxToken* pCurrentToken = currentToken();
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
            LanguageSyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);
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
        LanguageSyntaxToken* pCurrentToken = currentToken();

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
    LanguageSyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);

    return DelphiUnitModuleSyntax::create(_syntaxFactory, pHead, pInterfaceSection, pImplementationSection,
                                          endOfModule, pEOFToken, pInitializationSection, pFinalizationSection);
}

DelphiUnitHeadSyntax* DelphiParser::parseUnitHead() noexcept
{
    LanguageSyntaxToken* pUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    NameExpressionSyntax* pName = parseQualifiedName();
    LanguageSyntaxToken* pInKeyword{nullptr};
    LanguageSyntaxToken* pFilename{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken();
        pFilename = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    LanguageSyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUnitHeadSyntax::create(_syntaxFactory, pUnitKeyword, pName, pSemiColonToken, pInKeyword, pFilename);
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    LanguageSyntaxToken* pInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitInterfaceSectionSyntax::create(_syntaxFactory, pInterfaceKeyword, pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    LanguageSyntaxToken* pImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
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
    LanguageSyntaxToken* pUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    LanguageSyntaxList* pUnitReferences = _syntaxFactory.syntaxList();

    DelphiUnitReferenceDeclarationSyntax* pUnitReference = parseUnitReference();
    pUnitReferences->add(pUnitReference);

    while (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        LanguageSyntaxToken* pCommaToken = takeToken();
        pUnitReference = parseUnitReference();
        pUnitReferences->add(pCommaToken);
        pUnitReferences->add(pUnitReference);
    }

    LanguageSyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUsesClauseSyntax::create(_syntaxFactory, pUsesKeyword, pUnitReferences, pSemiColonToken);
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    NameExpressionSyntax* pUnitName = parseQualifiedName();
    LanguageSyntaxToken* pInKeyword{nullptr};
    LanguageSyntaxToken* pSourceFile{nullptr};

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
        LanguageSyntaxToken* pSeparator = takeToken();
        pName = parseQualifiedNameRight(pName, pSeparator);
    }

    return pName;
}

NameExpressionSyntax* DelphiParser::parseQualifiedNameRight(NameExpressionSyntax* left,
                                                            LanguageSyntaxToken* dotToken) noexcept
{
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    SimpleNameExpressionSyntax* pRight = parseIdentifierName();
    return QualifiedNameExpressionSyntax::create(_syntaxFactory, left, dotToken, pRight);
}

IdentifierNameExpressionSyntax* DelphiParser::parseIdentifierName() noexcept
{
    LanguageSyntaxToken* pCurrentToken = currentToken();

    if (pCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        LanguageSyntaxToken* pIdentifier = takeToken();
        return IdentifierNameExpressionSyntax::create(_syntaxFactory, pIdentifier);
    }
    else
    {
        LanguageSyntaxToken* pMissingIdentifier = _syntaxFactory.missingToken(SyntaxKind::IdentifierToken, pCurrentToken->text(), pCurrentToken->position());
        return IdentifierNameExpressionSyntax::create(_syntaxFactory, pMissingIdentifier);
    }
}

DelphiEndOfModuleSyntax* DelphiParser::parseEndOfModule() noexcept
{
    LanguageSyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    LanguageSyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    return DelphiEndOfModuleSyntax::create(_syntaxFactory, pEndKeyword, pDotToken);
}

} // end namespace polyglot::CodeAnalysis
