/*

    Copyright (c) 2015 Oliver Lau <ola@ct.de>, Heise Medien GmbH & Co. KG

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __TREEMODEL_H_
#define __TREEMODEL_H_

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QMimeData>
#include <QScopedPointer>


#include "domainnode.h"
#include "domainsettingslist.h"

class AbstractTreeNode;
class GroupNode;
class DomainTreeModelPrivate;

class DomainTreeModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit DomainTreeModel(QObject *parent = Q_NULLPTR);
  ~DomainTreeModel();

  QModelIndex populate(const DomainSettingsList &);
  DomainNode *node(const QModelIndex &index) const;
  void addNewGroup(const QModelIndex &index);
  QStringList getGroupHierarchy(const QModelIndex &index);
  void removeDomain(const QModelIndex &index);
  QModelIndex addDomain(QModelIndex &parentIndex, const DomainSettings &ds);
  DomainSettingsList getAllDomains();
  void appendDomains(GroupNode *groupNode, DomainSettingsList *domains);

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
  Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  Qt::DropActions supportedDropActions(void) const Q_DECL_OVERRIDE;
  QStringList mimeTypes(void) const Q_DECL_OVERRIDE;
  QMimeData *mimeData(const QModelIndexList &indexes) const Q_DECL_OVERRIDE;
  bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) Q_DECL_OVERRIDE;

signals:
  void groupNameChanged();

private:
  static GroupNode *findChild(const QString &name, GroupNode *node);
  static GroupNode *addToHierarchy(const QStringList &groups, GroupNode *node);
  void replaceGroupName(QString oldName, QString newName, GroupNode *node);

private: // member variables
  QScopedPointer<DomainTreeModelPrivate> d_ptr;
  Q_DECLARE_PRIVATE(DomainTreeModel)
  Q_DISABLE_COPY(DomainTreeModel)
};

#endif // __TREEMODEL_H_