/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _UIVISUQT_SNAPSHOTEDITOR_HPP_
#define _UIVISUQT_SNAPSHOTEDITOR_HPP_

#include <QObject>
#include <QPointer>

#include <fwTools/Failed.hpp>
#include <gui/editor/IEditor.hpp>

#include "uiVisuQt/config.hpp"

class QPushButton;

namespace uiVisu
{

/**
 * @brief   SnapshotEditor service is represented by a button. It allows to snap shot a generic scene.
 * @class   SnapshotEditor
 * 
 * @date    2010.
 */
class UIVISUQT_CLASS_API SnapshotEditor : public QObject, public ::gui::editor::IEditor
{

    Q_OBJECT

public :

    fwCoreServiceClassDefinitionsMacro ( (SnapshotEditor)(::gui::editor::IEditor) ) ;

    /// Constructor. Do nothing.
    UIVISUQT_API SnapshotEditor() throw() ;

    /// Destructor. Do nothing.
    UIVISUQT_API virtual ~SnapshotEditor() throw() ;

protected:

    typedef ::fwRuntime::ConfigurationElement::sptr Configuration;

    /**
     * @brief Install the layout.
     */
    virtual void starting() throw(::fwTools::Failed);

    /**
     * @brief Destroy the layout.
     */
    virtual void stopping() throw(::fwTools::Failed);

    /// Do nothing
    virtual void receiving( CSPTR(::fwServices::ObjectMsg) _msg ) throw(::fwTools::Failed);

    /// Do nothing
    virtual void updating() throw(::fwTools::Failed);

    /// Do nothing
    virtual void swapping() throw(::fwTools::Failed);

    /**
     * @brief Configure the editor.
     *
     * Example of configuration
     * @verbatim
    <service uid="snapshotEditor" type="::gui::editor::IEditor" impl="::uiVisu::SnapshotEditor" autoConnect="no">
        <snap>
            <scene uid="genericScene" />
        </snap>
    </service>
       @endverbatim
       \b genericScene is the uid of the ::fwRenderVTK::VtkRenderService representing the generic scene which will be printed.
     */
    virtual void configuring() throw(fwTools::Failed);

    /// Overrides
    virtual void info( std::ostream &_sstream ) ;

protected Q_SLOTS:
    /**
     * @brief Show a file dialog and notify the scene must be printed.
     */
    void onSnapButton();

private:
    std::string requestFileName();

    std::vector< std::string > m_scenesUID;

    QPointer< QPushButton > m_snapButton;

};

} // uiVisu

#endif /*_UIVISUQT_SNAPSHOTEDITOR_HPP_*/


