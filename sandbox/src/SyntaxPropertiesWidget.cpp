#include "SyntaxPropertiesWidget.hpp"
#include <QtCore/QString>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QVBoxLayout>
#include <sstream>
#include <string>
#include <string_view>
#include <polyglot/Core/LanguageKind.hpp>
#include <polyglot/Core/Syntax/ISyntaxList.hpp>
#include <polyglot/Core/Syntax/ISyntaxNode.hpp>
#include <polyglot/Core/Syntax/ISyntaxToken.hpp>
#include <polyglot/Core/Syntax/ISyntaxTrivia.hpp>
#include <polyglot/Core/Syntax/SyntaxKinds.hpp>
#include <polyglot/Core/Syntax/SyntaxVariant.hpp>
#include <polyglot/Core/Text/TextSpan.hpp>
#include "SyntaxTreeItem.hpp"

namespace ui
{

using namespace models;
using namespace polyglot::Core::Syntax;

// ----------------------------------------
// SyntaxPropertiesHeaderWidget
// ----------------------------------------

SyntaxPropertiesHeaderWidget::SyntaxPropertiesHeaderWidget(QWidget* parent) noexcept
    : QWidget{parent},
      _pLayout{new QFormLayout{this}},
      _pLblTypeName{new QLabel{this}},
      _pLblSyntaxKindName{new QLabel{this}}
{
    _pLayout->addRow(QStringLiteral("Type:"), _pLblTypeName);
    _pLayout->addRow(QStringLiteral("SyntaxKind:"), _pLblSyntaxKindName);
    setLayout(_pLayout);
}

void SyntaxPropertiesHeaderWidget::setTypeName(const QString& typeName) noexcept
{
    _pLblTypeName->setText(typeName);
}

void SyntaxPropertiesHeaderWidget::setSyntaxKindName(const QString& syntaxKindName) noexcept
{
    _pLblSyntaxKindName->setText(syntaxKindName);
}

// ----------------------------------------
// SyntaxPropertiesWidget
// ----------------------------------------

SyntaxPropertiesWidget::SyntaxPropertiesWidget(QWidget* parent) noexcept
    : QWidget{parent},
      _pVLayout{new QVBoxLayout{this}},
      _pLblHeader{new QLabel{QStringLiteral("Properties"), this}},
      _pPropertiesHeader{new SyntaxPropertiesHeaderWidget{this}},
      _pTblProperties{new QTableWidget{this}}
{
    _pTblProperties->horizontalHeader()->setVisible(false);
    _pTblProperties->verticalHeader()->setVisible(false);
    _pTblProperties->setEditTriggers(QAbstractItemView::NoEditTriggers);

    _pVLayout->addWidget(_pLblHeader);
    _pVLayout->addWidget(_pPropertiesHeader);
    _pVLayout->addWidget(_pTblProperties);

    setLayout(_pVLayout);
}

void SyntaxPropertiesWidget::onSyntaxSelected(const QModelIndex& index) noexcept
{
    if (index.isValid())
    {
        SyntaxTreeItem* pSelectedItem = static_cast<SyntaxTreeItem*>(index.internalPointer());

        if (pSelectedItem != nullptr)
        {
            const SyntaxVariant& syntaxItem = pSelectedItem->value();
            SyntaxKind syntaxKind = SyntaxKind::None;
            std::string typeName;

            if (syntaxItem.isNode())
            {
                syntaxKind = syntaxItem.node->syntaxKind();
                typeName = syntaxItem.node->typeName();
                updateValues(syntaxItem.node);
            }
            else if (syntaxItem.isToken())
            {
                syntaxKind = syntaxItem.token->syntaxKind();
                typeName = syntaxItem.token->typeName();
                updateValues(syntaxItem.token);
            }
            else if (syntaxItem.isTrivia())
            {
                syntaxKind = syntaxItem.trivia->syntaxKind();
                typeName = syntaxItem.trivia->typeName();
                updateValues(syntaxItem.trivia);
            }
            else if (syntaxItem.isList())
            {
                syntaxKind = syntaxItem.list->syntaxKind();
                typeName = syntaxItem.list->typeName();
                updateValues(syntaxItem.list);
            }

            _pPropertiesHeader->setTypeName(QString::fromStdString(typeName));
            _pPropertiesHeader->setSyntaxKindName(QString::fromStdString(syntaxKindName(syntaxKind)));
        }
    }
}

QString convertStrViewToStr(std::string_view value) noexcept
{
    std::stringstream str;
    str << value;
    const std::string strValue = str.str();
    return QString::fromStdString(strValue);
}

void SyntaxPropertiesWidget::updateValues(polyglot::Core::Syntax::ISyntaxList* syntaxList) noexcept
{
    if (syntaxList != nullptr)
    {
        _pTblProperties->clear();
        _pTblProperties->setRowCount(16);
        _pTblProperties->setColumnCount(2);
        _pTblProperties->setColumnWidth(0, 150);
        _pTblProperties->setColumnWidth(1, 200);

        addPropertyRow(0, 0, QStringLiteral("LanguageKind"));
        addPropertyRow(0, 1, QString::fromStdString(polyglot::Core::languageKindName(syntaxList->languageKind())));

        addPropertyRow(1, 0, QStringLiteral("Text"));
        addPropertyRow(1, 1, convertStrViewToStr(syntaxList->text()));

        addPropertyRow(2, 0, QStringLiteral("Text incl. Trivia"));
        addPropertyRow(2, 1, convertStrViewToStr(syntaxList->textIncludingTrivia()));

        addPropertyRow(3, 0, QStringLiteral("Has Missing Tokens"));
        addPropertyRow(3, 1, syntaxList->hasMissingTokens() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(4, 0, QStringLiteral("Position"));
        addPropertyRow(4, 1, QStringLiteral("%1").arg(syntaxList->position()));

        addPropertyRow(5, 0, QStringLiteral("End Position"));
        addPropertyRow(5, 1, QStringLiteral("%1").arg(syntaxList->endPosition()));

        addPropertyRow(6, 0, QStringLiteral("Width"));
        addPropertyRow(6, 1, QStringLiteral("%1").arg(syntaxList->width()));

        addPropertyRow(7, 0, QStringLiteral("Span"));
        addPropertyRow(7, 1, QString::fromStdString(syntaxList->span().toString()));

        addPropertyRow(8, 0, QStringLiteral("Position incl. Trivia"));
        addPropertyRow(8, 1, QStringLiteral("%1").arg(syntaxList->positionIncludingTrivia()));

        addPropertyRow(9, 0, QStringLiteral("End Position incl. Trivia"));
        addPropertyRow(9, 1, QStringLiteral("%1").arg(syntaxList->endPositionIncludingTrivia()));

        addPropertyRow(10, 0, QStringLiteral("Full Width"));
        addPropertyRow(10, 1, QStringLiteral("%1").arg(syntaxList->fullWidth()));

        addPropertyRow(11, 0, QStringLiteral("Full Span"));
        addPropertyRow(11, 1, QString::fromStdString(syntaxList->fullSpan().toString()));

        addPropertyRow(12, 0, QStringLiteral("Has Leading Trivia"));
        addPropertyRow(12, 1, syntaxList->hasLeadingTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(13, 0, QStringLiteral("Leading Trivia Width"));
        addPropertyRow(13, 1, QStringLiteral("%1").arg(syntaxList->leadingTriviaWidth()));

        addPropertyRow(14, 0, QStringLiteral("Has Trailing Trivia"));
        addPropertyRow(14, 1, syntaxList->hasTrailingTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(15, 0, QStringLiteral("Trailing Trivia Width"));
        addPropertyRow(15, 1, QStringLiteral("%1").arg(syntaxList->trailingTriviaWidth()));
    }
}

void SyntaxPropertiesWidget::updateValues(polyglot::Core::Syntax::ISyntaxNode* syntaxNode) noexcept
{
    if (syntaxNode != nullptr)
    {
        _pTblProperties->clear();
        _pTblProperties->setRowCount(19);
        _pTblProperties->setColumnCount(2);
        _pTblProperties->setColumnWidth(0, 150);
        _pTblProperties->setColumnWidth(1, 200);

        addPropertyRow(0, 0, QStringLiteral("LanguageKind"));
        addPropertyRow(0, 1, QString::fromStdString(polyglot::Core::languageKindName(syntaxNode->languageKind())));

        addPropertyRow(1, 0, QStringLiteral("Text"));
        addPropertyRow(1, 1, convertStrViewToStr(syntaxNode->text()));

        addPropertyRow(2, 0, QStringLiteral("Text incl. Trivia"));
        addPropertyRow(2, 1, convertStrViewToStr(syntaxNode->textIncludingTrivia()));

        addPropertyRow(3, 0, QStringLiteral("Is Expression"));
        addPropertyRow(3, 1, syntaxNode->isExpression() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(4, 0, QStringLiteral("Is Statement"));
        addPropertyRow(4, 1, syntaxNode->isStatement() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(5, 0, QStringLiteral("Is Declaration"));
        addPropertyRow(5, 1, syntaxNode->isDeclaration() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(6, 0, QStringLiteral("Is Clause"));
        addPropertyRow(6, 1, syntaxNode->isClause() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(7, 0, QStringLiteral("Has Missing Tokens"));
        addPropertyRow(7, 1, syntaxNode->hasMissingTokens() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(8, 0, QStringLiteral("Position"));
        addPropertyRow(8, 1, QStringLiteral("%1").arg(syntaxNode->position()));

        addPropertyRow(9, 0, QStringLiteral("End Position"));
        addPropertyRow(9, 1, QStringLiteral("%1").arg(syntaxNode->endPosition()));

        addPropertyRow(10, 0, QStringLiteral("Width"));
        addPropertyRow(10, 1, QStringLiteral("%1").arg(syntaxNode->width()));

        addPropertyRow(11, 0, QStringLiteral("Span"));
        addPropertyRow(11, 1, QString::fromStdString(syntaxNode->span().toString()));

        addPropertyRow(12, 0, QStringLiteral("Position incl. Trivia"));
        addPropertyRow(12, 1, QStringLiteral("%1").arg(syntaxNode->positionIncludingTrivia()));

        addPropertyRow(13, 0, QStringLiteral("End Position incl. Trivia"));
        addPropertyRow(13, 1, QStringLiteral("%1").arg(syntaxNode->endPositionIncludingTrivia()));

        addPropertyRow(14, 0, QStringLiteral("Full Span"));
        addPropertyRow(14, 1, QString::fromStdString(syntaxNode->fullSpan().toString()));

        addPropertyRow(15, 0, QStringLiteral("Has Leading Trivia"));
        addPropertyRow(15, 1, syntaxNode->hasLeadingTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(16, 0, QStringLiteral("Leading Trivia Width"));
        addPropertyRow(16, 1, QStringLiteral("%1").arg(syntaxNode->leadingTriviaWidth()));

        addPropertyRow(17, 0, QStringLiteral("Has Trailing Trivia"));
        addPropertyRow(17, 1, syntaxNode->hasTrailingTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(18, 0, QStringLiteral("Trailing Trivia Width"));
        addPropertyRow(18, 1, QStringLiteral("%1").arg(syntaxNode->trailingTriviaWidth()));
    }
}

void SyntaxPropertiesWidget::updateValues(polyglot::Core::Syntax::ISyntaxToken* syntaxToken) noexcept
{
    if (syntaxToken != nullptr)
    {
        _pTblProperties->clear();
        _pTblProperties->setRowCount(19);
        _pTblProperties->setColumnCount(2);
        _pTblProperties->setColumnWidth(0, 150);
        _pTblProperties->setColumnWidth(1, 200);

        addPropertyRow(0, 0, QStringLiteral("LanguageKind"));
        addPropertyRow(0, 1, QString::fromStdString(polyglot::Core::languageKindName(syntaxToken->languageKind())));

        addPropertyRow(1, 0, QStringLiteral("Text"));
        addPropertyRow(1, 1, convertStrViewToStr(syntaxToken->text()));

        addPropertyRow(2, 0, QStringLiteral("Text incl. Trivia"));
        addPropertyRow(2, 1, convertStrViewToStr(syntaxToken->textIncludingTrivia()));

        addPropertyRow(3, 0, QStringLiteral("Is Identifier"));
        addPropertyRow(3, 1, syntaxToken->isIdentifier() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(4, 0, QStringLiteral("Is Keyword"));
        addPropertyRow(4, 1, syntaxToken->isKeyword() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(5, 0, QStringLiteral("Is Literal"));
        addPropertyRow(5, 1, syntaxToken->isLiteral() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(6, 0, QStringLiteral("Is Punctuation"));
        addPropertyRow(6, 1, syntaxToken->isPunctuation() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(7, 0, QStringLiteral("Is Missing"));
        addPropertyRow(7, 1, syntaxToken->isMissing() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(8, 0, QStringLiteral("Position"));
        addPropertyRow(8, 1, QStringLiteral("%1").arg(syntaxToken->position()));

        addPropertyRow(9, 0, QStringLiteral("End Position"));
        addPropertyRow(9, 1, QStringLiteral("%1").arg(syntaxToken->endPosition()));

        addPropertyRow(10, 0, QStringLiteral("Width"));
        addPropertyRow(10, 1, QStringLiteral("%1").arg(syntaxToken->width()));

        addPropertyRow(11, 0, QStringLiteral("Span"));
        addPropertyRow(11, 1, QString::fromStdString(syntaxToken->span().toString()));

        addPropertyRow(12, 0, QStringLiteral("Position incl. Trivia"));
        addPropertyRow(12, 1, QStringLiteral("%1").arg(syntaxToken->positionIncludingTrivia()));

        addPropertyRow(13, 0, QStringLiteral("End Position incl. Trivia"));
        addPropertyRow(13, 1, QStringLiteral("%1").arg(syntaxToken->endPositionIncludingTrivia()));

        addPropertyRow(14, 0, QStringLiteral("Full Span"));
        addPropertyRow(14, 1, QString::fromStdString(syntaxToken->fullSpan().toString()));

        addPropertyRow(15, 0, QStringLiteral("Has Leading Trivia"));
        addPropertyRow(15, 1, syntaxToken->hasLeadingTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(16, 0, QStringLiteral("Leading Trivia Width"));
        addPropertyRow(16, 1, QStringLiteral("%1").arg(syntaxToken->leadingTriviaWidth()));

        addPropertyRow(17, 0, QStringLiteral("Has Trailing Trivia"));
        addPropertyRow(17, 1, syntaxToken->hasTrailingTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(18, 0, QStringLiteral("Trailing Trivia Width"));
        addPropertyRow(18, 1, QStringLiteral("%1").arg(syntaxToken->trailingTriviaWidth()));
    }
}

void SyntaxPropertiesWidget::updateValues(polyglot::Core::Syntax::ISyntaxTrivia* syntaxTrivia) noexcept
{
    if (syntaxTrivia != nullptr)
    {
        _pTblProperties->clear();
        _pTblProperties->setRowCount(13);
        _pTblProperties->setColumnCount(2);
        _pTblProperties->setColumnWidth(0, 150);
        _pTblProperties->setColumnWidth(1, 200);

        addPropertyRow(0, 0, QStringLiteral("LanguageKind"));
        addPropertyRow(0, 1, QString::fromStdString(polyglot::Core::languageKindName(syntaxTrivia->languageKind())));

        addPropertyRow(1, 0, QStringLiteral("Text"));
        addPropertyRow(1, 1, convertStrViewToStr(syntaxTrivia->text()));

        addPropertyRow(2, 0, QStringLiteral("Is Leading"));
        addPropertyRow(2, 1, syntaxTrivia->isLeading() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(3, 0, QStringLiteral("Is Trailing"));
        addPropertyRow(3, 1, syntaxTrivia->isTrailing() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(4, 0, QStringLiteral("Is Whitespace"));
        addPropertyRow(4, 1, syntaxTrivia->isWhitespace() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(5, 0, QStringLiteral("Is Line Ending"));
        addPropertyRow(5, 1, syntaxTrivia->isLineEnding() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(6, 0, QStringLiteral("Is Structured Trivia"));
        addPropertyRow(6, 1, syntaxTrivia->isStructuredTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(7, 0, QStringLiteral("Is Directive"));
        addPropertyRow(7, 1, syntaxTrivia->isDirective() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(8, 0, QStringLiteral("Is Skipped Tokens Trivia"));
        addPropertyRow(8, 1, syntaxTrivia->isSkippedTokensTrivia() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(9, 0, QStringLiteral("Is Comment"));
        addPropertyRow(9, 1, syntaxTrivia->isComment() ? QStringLiteral("True") : QStringLiteral("False"));

        addPropertyRow(10, 0, QStringLiteral("Position"));
        addPropertyRow(10, 1, QStringLiteral("%1").arg(syntaxTrivia->position()));

        addPropertyRow(11, 0, QStringLiteral("End Position"));
        addPropertyRow(11, 1, QStringLiteral("%1").arg(syntaxTrivia->endPosition()));

        addPropertyRow(11, 0, QStringLiteral("Width"));
        addPropertyRow(11, 1, QStringLiteral("%1").arg(syntaxTrivia->width()));

        addPropertyRow(12, 0, QStringLiteral("Span"));
        addPropertyRow(12, 1, QString::fromStdString(syntaxTrivia->span().toString()));
    }
}

void SyntaxPropertiesWidget::addPropertyRow(int row,
                                            int column,
                                            const QString& value) noexcept
{
    _pTblProperties->setItem(row, column, new QTableWidgetItem{value});
}

} // end namespace ui
