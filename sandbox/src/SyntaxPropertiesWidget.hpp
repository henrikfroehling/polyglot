#ifndef POLYGLOT_SANDBOX_SYNTAXPROPERTIESWIDGET_H
#define POLYGLOT_SANDBOX_SYNTAXPROPERTIESWIDGET_H

#include <QtWidgets/QWidget>

class QFormLayout;
class QLabel;
class QModelIndex;
class QString;
class QTableWidget;
class QVBoxLayout;

namespace polyglot::Core::Syntax
{

class ISyntaxList;
class ISyntaxNode;
class ISyntaxToken;
class ISyntaxTrivia;

} // end namespace polyglot::Core::Syntax

namespace ui
{

// ----------------------------------------
// SyntaxPropertiesHeaderWidget
// ----------------------------------------

class SyntaxPropertiesHeaderWidget : public QWidget
{
public:
    explicit SyntaxPropertiesHeaderWidget(QWidget* parent = nullptr) noexcept;
    void setTypeName(const QString& typeName) noexcept;
    void setSyntaxKindName(const QString& syntaxKindName) noexcept;

private:
    QFormLayout* _pLayout;
    QLabel* _pLblTypeName;
    QLabel* _pLblSyntaxKindName;
};

// ----------------------------------------
// SyntaxPropertiesWidget
// ----------------------------------------

class SyntaxPropertiesWidget : public QWidget
{
public:
    explicit SyntaxPropertiesWidget(QWidget* parent = nullptr) noexcept;

public slots:
    void onSyntaxSelected(const QModelIndex& index) noexcept;

private:
    void updateValues(polyglot::Core::Syntax::ISyntaxList* syntaxList) noexcept;
    void updateValues(polyglot::Core::Syntax::ISyntaxNode* syntaxNode) noexcept;
    void updateValues(polyglot::Core::Syntax::ISyntaxToken* syntaxToken) noexcept;
    void updateValues(polyglot::Core::Syntax::ISyntaxTrivia* syntaxTrivia) noexcept;

    void addPropertyRow(int row,
                        int column,
                        const QString& value) noexcept;

private:
    QVBoxLayout* _pVLayout;
    QLabel* _pLblHeader;
    SyntaxPropertiesHeaderWidget* _pPropertiesHeader;
    QTableWidget* _pTblProperties;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_SYNTAXPROPERTIESWIDGET_H
