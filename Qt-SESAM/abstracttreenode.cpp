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

#include <QDebug>
#include "abstracttreenode.h"

AbstractTreeNode::AbstractTreeNode(AbstractTreeNode *parentItem)
  : mParentItem(parentItem)
{
  /* ... */
}

AbstractTreeNode::~AbstractTreeNode()
{
  qDeleteAll(mChildItems);
}


void AbstractTreeNode::appendChild(AbstractTreeNode *item)
{
  mChildItems.append(item);
}


void AbstractTreeNode::removeChild(AbstractTreeNode *item)
{

  mChildItems.removeOne(item);
}


AbstractTreeNode *AbstractTreeNode::child(int row)
{
  return mChildItems.at(row);
}


int AbstractTreeNode::childCount(void) const
{
  return mChildItems.count();
}


AbstractTreeNode *AbstractTreeNode::parentItem(void)
{
  return mParentItem;
}


int AbstractTreeNode::row(void) const
{
  return (mParentItem == Q_NULLPTR)
      ? 0
      : mParentItem->mChildItems.indexOf(const_cast<AbstractTreeNode*>(this));
}


int AbstractTreeNode::columnCount(void) const
{
  return 4;
}


QVariant AbstractTreeNode::data(int) const
{
  return QVariant();
}
