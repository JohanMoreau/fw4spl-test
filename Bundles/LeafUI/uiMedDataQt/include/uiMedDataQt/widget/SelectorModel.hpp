/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2013.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIMEDDATAQT_WIDGET_SELECTORMODEL_HPP__
#define __UIMEDDATAQT_WIDGET_SELECTORMODEL_HPP__

#include <map>

#include <QString>
#include <QTreeView>
#include <QPointer>
#include <QStandardItemModel>
#include <QStandardItem>

#include <fwMedData/Series.hpp>

#include "uiMedDataQt/config.hpp"

namespace uiMedData
{
namespace widget
{

/**
 * @brief   This class represents the Selector Model.
 * @class   SSelector.
 * @date    2013.
 */
class UIMEDDATAQT_CLASS_API SelectorModel : public QStandardItemModel
{
    Q_OBJECT

public:

    typedef enum
    {
        ITEM_TYPE = Qt::UserRole, /// Role for the item type (STUDY or SERIES)
        UID                       /// Role for the fwID of the object
    }Role;

    typedef enum
    {
        STUDY = 1,  /// Type to represent Study/Patient
        SERIES      /// Type to represent Series
    }ItemType;

    /// Constructor. Inits the model.
    UIMEDDATAQT_API SelectorModel(QWidget *parent = 0);

    /// Destructor. Does nothing
    UIMEDDATAQT_API ~SelectorModel();

    /**
     * @brief Add the Series in the tree. If the associated study already exist in the tree, the series is added to
     * this study.
     */
    UIMEDDATAQT_API void addSeries(::fwMedData::Series::sptr series);

    /**
     * @brief Removes the Series from the tree. After deletion, if the study is empty, it will be removed.
     * @param[in] series series to remove from the tree.
     */
    UIMEDDATAQT_API void removeSeries(::fwMedData::Series::sptr series);

    /// Clears all items in the model.
    UIMEDDATAQT_API void clear();

    /// Returns item flags with non editable flag
    UIMEDDATAQT_API Qt::ItemFlags flags(const QModelIndex& index) const
    {
        return (QStandardItemModel::flags(index) & ~Qt::ItemIsEditable);
    }

    /// Returns the type of the item (SERIES or STUDY) associated to the ITEM_TYPE role.
    UIMEDDATAQT_API ItemType getItemType(const QModelIndex &index);

    /**
     * @brief Returns the index in the same row as the given index and at the specified column.
     * @param[in] index index used to get the associated row.
     * @param[in] column the column of the index to return.
     */
    UIMEDDATAQT_API QModelIndex getIndex(const QModelIndex& index, int column );

    /// Removes the rows given by the indexes.
    UIMEDDATAQT_API void removeRows(const QModelIndexList indexes);

    /// Returns the series item representing the series.
    UIMEDDATAQT_API QStandardItem* findSeriesItem(::fwMedData::Series::sptr series);


private:

    typedef std::map< ::fwMedData::DicomValueType, QStandardItem* > StudyUidItemMapType;

    /**
     * @brief Returns the informations contained in the data container as a string, all items are separated by the
     * separator.
     */
    template <typename T>
    QStandardItem* getInfo(T data, QString separator);

    /// Removes the study item and all the series associated.
    bool removeStudyItem(QStandardItem *item);

    /// Removes the series item and the parent study if it is the last series in the study.
    bool removeSeriesItem(QStandardItem *item);

    /// Add the icon corresponding to the type of series.
    void addSeriesIcon(::fwMedData::Series::sptr series, QStandardItem *item);

    /// Initializes model. Sets headers of the selector.
    void init();

    /// Number of study rows in the tree.
    int m_studyRowCount;

    /**
     * @brief Map to register the association of study Instance UID  and study root item.
     * It is used to associate the series to its study in the tree.
     */
    StudyUidItemMapType m_items;
};


template <typename T>
QStandardItem* SelectorModel::getInfo(T data, QString separator)
{
    QString dataStr;
    if(!data.empty())
    {
        typename T::iterator itr = data.begin();
        std::ostringstream str;
        str << *itr++;
        dataStr = QString::fromStdString(str.str());

        for(;itr!= data.end(); ++itr)
        {
            str.str("");
            str << *itr;
            dataStr.append(separator + QString::fromStdString(str.str()));
        }
    }
    QStandardItem *item = new QStandardItem(dataStr);
    return item;
}


} // namespace widget
} // namespace uiMedData

#endif // __UIMEDDATAQT_WIDGET_SELECTORMODEL_HPP__