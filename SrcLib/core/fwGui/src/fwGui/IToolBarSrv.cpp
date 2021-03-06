/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <boost/foreach.hpp>

#include <fwCore/base.hpp>
#include <fwTools/fwID.hpp>
#include <fwServices/Base.hpp>

#include "fwGui/IMenuItemCallback.hpp"
#include "fwGui/IToolBarSrv.hpp"
#include "fwGui/IActionSrv.hpp"

namespace fwGui
{

IToolBarSrv::IToolBarSrv() : m_hideActions (false)
{}

//-----------------------------------------------------------------------------

IToolBarSrv::~IToolBarSrv()
{}

//-----------------------------------------------------------------------------

void IToolBarSrv::initialize()
{
    m_registrar = ::fwGui::registrar::ToolBarRegistrar::New(this->getID());
    // find ViewRegistryManager configuration
    std::vector < ConfigurationType > vectRegistrar = m_configuration->find("registry");
    SLM_ASSERT("Registry section is mandatory.", !vectRegistrar.empty() );

    if(!vectRegistrar.empty())
    {
        m_registrarConfig = vectRegistrar.at(0);
        m_registrar->initialize(m_registrarConfig);
    }

    // find gui configuration
    std::vector < ConfigurationType > vectGui = m_configuration->find("gui");
    SLM_ASSERT("Gui section is mandatory.", !vectGui.empty() );

    if(!vectGui.empty())
    {
        // find LayoutManager configuration
        std::vector < ConfigurationType > vectLayoutMng = vectGui.at(0)->find("layout");
        SLM_ASSERT("layout section is mandatory.", !vectLayoutMng.empty() );

        if(!vectLayoutMng.empty())
        {
            m_layoutConfig = vectLayoutMng.at(0);
            this->initializeLayoutManager(m_layoutConfig);
        }
    }
}

//-----------------------------------------------------------------------------

void IToolBarSrv::create()
{
    ::fwGui::container::fwToolBar::sptr toolBar = m_registrar->getParent();
    std::vector< ::fwGui::IMenuItemCallback::sptr > callbacks = m_registrar->getCallbacks();

    SLM_ASSERT("Parent toolBar is unknown.", toolBar);
    m_layoutManager->setCallbacks(callbacks);
    m_layoutManager->createLayout(toolBar);

    m_registrar->manage(m_layoutManager->getMenuItems());
    m_registrar->manage(m_layoutManager->getMenus());
    m_registrar->manage(m_layoutManager->getContainers());
}

//-----------------------------------------------------------------------------

void IToolBarSrv::destroy()
{
    m_registrar->unmanage();
    m_layoutManager->destroyLayout();
}

//-----------------------------------------------------------------------------

void IToolBarSrv::actionServiceStopping(std::string actionSrvSID)
{
    ::fwGui::container::fwMenuItem::sptr menuItem = m_registrar->getFwMenuItem(actionSrvSID, m_layoutManager->getMenuItems());

    if (m_hideActions)
    {
        m_layoutManager->menuItemSetVisible(menuItem, false);
    }
    else
    {
        m_layoutManager->menuItemSetEnabled(menuItem, false);
    }
}

//-----------------------------------------------------------------------------

void IToolBarSrv::actionServiceStarting(std::string actionSrvSID)
{
    ::fwGui::container::fwMenuItem::sptr menuItem = m_registrar->getFwMenuItem(actionSrvSID, m_layoutManager->getMenuItems());

    if (m_hideActions)
    {
        m_layoutManager->menuItemSetVisible(menuItem, true);
    }
    else
    {
        ::fwServices::IService::sptr service = ::fwServices::get( actionSrvSID ) ;
        ::fwGui::IActionSrv::sptr actionSrv = ::fwGui::IActionSrv::dynamicCast(service);
        m_layoutManager->menuItemSetEnabled(menuItem, actionSrv->getIsExecutable());
    }
}

//-----------------------------------------------------------------------------

void IToolBarSrv::actionServiceSetActive(std::string actionSrvSID, bool isActive)
{
    ::fwGui::container::fwMenuItem::sptr menuItem = m_registrar->getFwMenuItem(actionSrvSID, m_layoutManager->getMenuItems());

    m_layoutManager->menuItemSetChecked(menuItem, isActive);

}

//-----------------------------------------------------------------------------

void IToolBarSrv::actionServiceSetExecutable(std::string actionSrvSID, bool isExecutable)
{
    ::fwGui::container::fwMenuItem::sptr menuItem = m_registrar->getFwMenuItem(actionSrvSID, m_layoutManager->getMenuItems());

    m_layoutManager->menuItemSetEnabled(menuItem, isExecutable);

}

//-----------------------------------------------------------------------------

void IToolBarSrv::initializeLayoutManager(ConfigurationType layoutConfig)
{
    OSLM_ASSERT("Bad configuration name "<<layoutConfig->getName()<< ", must be layout",
            layoutConfig->getName() == "layout");

    ::fwGui::GuiBaseObject::sptr guiObj = ::fwGui::factory::New(
                                                 ::fwGui::layoutManager::IToolBarLayoutManager::REGISTRY_KEY);
    m_layoutManager = ::fwGui::layoutManager::IToolBarLayoutManager::dynamicCast(guiObj);
    OSLM_ASSERT("ClassFactoryRegistry failed for class "<< ::fwGui::layoutManager::IToolBarLayoutManager::REGISTRY_KEY, m_layoutManager);

    m_layoutManager->initialize(layoutConfig);
}

//-----------------------------------------------------------------------------

}
