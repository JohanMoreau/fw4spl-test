/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2014.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */


#include "fwGui/dialog/MessageDialog.hpp"

namespace fwGui
{
namespace dialog
{

//-----------------------------------------------------------------------------

IMessageDialog::Buttons MessageDialog::showMessageDialog(const std::string& title, const std::string& message, ::fwGui::dialog::IMessageDialog::Icons icon)
{
    ::fwGui::dialog::MessageDialog  messageBox(title, message, icon);
    messageBox.addButton(::fwGui::dialog::IMessageDialog::OK);
    return messageBox.show();
}

//-----------------------------------------------------------------------------

MessageDialog::MessageDialog()
{
    ::fwGui::GuiBaseObject::sptr guiObj = ::fwGui::factory::New(IMessageDialog::REGISTRY_KEY);
    m_implementation = ::fwGui::dialog::IMessageDialog::dynamicCast(guiObj);
}

//-----------------------------------------------------------------------------

MessageDialog::MessageDialog(const std::string& title, const std::string& message, ::fwGui::dialog::IMessageDialog::Icons icon)
{
    ::fwGui::GuiBaseObject::sptr guiObj = ::fwGui::factory::New(IMessageDialog::REGISTRY_KEY);
    m_implementation = ::fwGui::dialog::IMessageDialog::dynamicCast(guiObj);
    if(m_implementation)
    {
        m_implementation->setTitle(title);
        m_implementation->setMessage(message);
        m_implementation->setIcon(icon);
    }
}

//-----------------------------------------------------------------------------

MessageDialog::~MessageDialog()
{}

//-----------------------------------------------------------------------------

void MessageDialog::setTitle( const std::string &title )
{
    if(m_implementation)
    {
        m_implementation->setTitle(title);
    }
}

//-----------------------------------------------------------------------------

void MessageDialog::setMessage( const std::string &msg )
{
    if(m_implementation)
    {
        m_implementation->setMessage(msg);
    }
}

//-----------------------------------------------------------------------------

void MessageDialog::setIcon( ::fwGui::dialog::IMessageDialog::Icons icon )
{
    if(m_implementation)
    {
        m_implementation->setIcon(icon);
    }
}

//-----------------------------------------------------------------------------

void MessageDialog::addButton( ::fwGui::dialog::IMessageDialog::Buttons button )
{
    if(m_implementation)
    {
        m_implementation->addButton(button);
    }
}

//-----------------------------------------------------------------------------

void MessageDialog::setDefaultButton( ::fwGui::dialog::IMessageDialog::Buttons button )
{
    if(m_implementation)
    {
        m_implementation->setDefaultButton(button);
    }
}

//-----------------------------------------------------------------------------

::fwGui::dialog::IMessageDialog::Buttons MessageDialog::show()
{
    if(m_implementation)
    {
        return m_implementation->show();
    }
    else
    {
        return ::fwGui::dialog::IMessageDialog::NOBUTTON;
    }
}

//-----------------------------------------------------------------------------

} //namespace dialog
} // namespace fwGui



