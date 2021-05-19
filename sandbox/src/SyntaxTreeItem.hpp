#ifndef POLYGLOT_SANDBOX_SYNTAXTREEITEM_H
#define POLYGLOT_SANDBOX_SYNTAXTREEITEM_H

#include <memory>
#include <vector>
#include <QtCore/QVariant>
#include <polyglot/Core/Syntax/SyntaxVariant.hpp>

namespace models
{

class SyntaxTreeItem
{
public:
    SyntaxTreeItem() noexcept;

    explicit SyntaxTreeItem(polyglot::Core::Syntax::SyntaxVariant value,
                            SyntaxTreeItem* parent = nullptr) noexcept;

    ~SyntaxTreeItem() noexcept {}

    inline SyntaxTreeItem* parentItem() const noexcept { return _pParentItem; }
    inline int childCount() const noexcept { return _children.size(); }
    inline int row() const noexcept { return _row; }
    inline const polyglot::Core::Syntax::SyntaxVariant& value() const noexcept { return _value; }
    SyntaxTreeItem* child(int row) const noexcept;
    QVariant data() const noexcept;
    void add(polyglot::Core::Syntax::SyntaxVariant value) noexcept;
    void clear() noexcept;

private:
    inline void setRow(int row) noexcept { _row = row; }

private:
    std::vector<std::unique_ptr<SyntaxTreeItem>> _children;
    polyglot::Core::Syntax::SyntaxVariant _value;
    int _row;
    SyntaxTreeItem* _pParentItem;
};

} // end namespace models

#endif // POLYGLOT_SANDBOX_SYNTAXTREEITEM_H
