/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWDATA_UT_TRANSFORMATION3DMATRIXTEST_HPP__
#define __FWDATA_UT_TRANSFORMATION3DMATRIXTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

namespace fwData
{
namespace ut
{

class TransformationMatrix3DTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TransformationMatrix3DTest );
    CPPUNIT_TEST( methode1 );
    CPPUNIT_TEST( methode2 );
    CPPUNIT_TEST_SUITE_END();

public:
    // interface
    void setUp();
    void tearDown();

    void methode1();
    void methode2();
};

} //namespace ut
} //namespace fwData
#endif //__FWDATA_UT_TRANSFORMATION3DMATRIXTEST_HPP__
