#include "CodeAnalysis/Delphi/Parser/DelphiParser.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "CodeAnalysis/Delphi/Parser/DelphiLexer.hpp"
#include "CodeAnalysis/Delphi/Parser/DelphiSyntaxFacts.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
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
    DelphiUnitHeadingSyntax* pHeading = nullptr;
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
                pHeading = parseUnitHeading();
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
    LanguageSyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    LanguageSyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    LanguageSyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);

    return DelphiUnitModuleSyntax::create(_syntaxFactory, pHeading, pInterfaceSection, pImplementationSection, pEndKeyword,
                                          pDotToken, pEOFToken, pInitializationSection, pFinalizationSection);
}

DelphiUnitHeadingSyntax* DelphiParser::parseUnitHeading() noexcept
{
    LanguageSyntaxToken* pUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    NameExpressionSyntax* pName = parseQualifiedName();
    LanguageSyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUnitHeadingSyntax::create(_syntaxFactory, pUnitKeyword, pName, pSemiColonToken);
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    LanguageSyntaxToken* pInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    DelphiUsesClauseSyntax* pUses = parseUsesClause();
    return DelphiUnitInterfaceSectionSyntax::create(_syntaxFactory, pInterfaceKeyword, pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    LanguageSyntaxToken* pImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    DelphiUsesClauseSyntax* pUses = parseUsesClause();
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
    std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences{};

    while (true)
    {
        if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
            break;

        DelphiUnitReferenceDeclarationSyntax* pUnitReference = parseUnitReference();
        unitReferences.push_back(pUnitReference);
    }

    LanguageSyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUsesClauseSyntax::create(_syntaxFactory, pUsesKeyword, std::move(unitReferences), pSemiColonToken);
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    NameExpressionSyntax* pUnitName = parseQualifiedName();
    LanguageSyntaxToken* pInKeyword{nullptr};
    LanguageSyntaxToken* pSourceFile{nullptr};
    LanguageSyntaxToken* pCommaToken{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken(SyntaxKind::InKeyword);
        pSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    if (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
        pCommaToken = takeToken(SyntaxKind::CommaToken);

    return DelphiUnitReferenceDeclarationSyntax::create(_syntaxFactory, pUnitName, pInKeyword, pSourceFile, pCommaToken);
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

} // end namespace polyglot::CodeAnalysis
