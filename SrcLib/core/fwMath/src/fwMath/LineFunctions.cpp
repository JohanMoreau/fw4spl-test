/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwMath/LineFunctions.hpp"
#include "fwMath/VectorFunctions.hpp"
#include "fwMath/PlaneFunctions.hpp"

namespace fwMath {

//------------------------------------------------------------------------------

bool getClosestPoints( const fwLine& _line1, const fwLine& _line2, fwVec3d& _pointOnThis, fwVec3d& _pointOnfwLine)
{
    SLM_TRACE_FUNC();
    const fwVec3d& pos1 = _line1.first;
    const fwVec3d& dir1 = _line1.second;

    const fwVec3d& pos2 = _line2.first;
    const fwVec3d& dir2 = _line2.second;

    double dd = dot(dir1, dir2);
    double delta = 1.0F - dd * dd;

    if((float)delta==0.0F) return false;

    double t2 = ( dot(dir2, pos1 - pos2) -  dot(dir1, pos1-pos2) * dd)/delta;
    double t1  = ( -dot(dir1, pos1 - pos2) + dot(dir2, pos1-pos2) * dd)/delta;

    _pointOnThis = pos1 + t1 * dir1;
    _pointOnfwLine = pos2 + t2 * dir2;

    return true;
}

//------------------------------------------------------------------------------

fwVec3d getClosestPoint( const fwLine& _line, fwVec3d& _point)
{
    SLM_TRACE_FUNC();
    const fwVec3d& pos = _line.first;
    const fwVec3d& dir = _line.second;

    double t = dot(_point - pos,dir);
    return (pos + t * dir);
}

//------------------------------------------------------------------------------

bool intersect(const fwLine& _line, double _radius, fwVec3d _point)
{
    SLM_TRACE_FUNC();
    fwVec3d point = getClosestPoint(_line, _point);
    fwVec3d tmp = _point-point;
    double length = vecLength(tmp);
    if(length>_radius) return false;
    return true;
}

//------------------------------------------------------------------------------

bool intersect(const fwLine& _line, double _radius,fwVec3d _vec0, fwVec3d _vec1, fwVec3d _point)
{
    SLM_TRACE_FUNC();
    fwLine line = std::pair<fwVec3d, fwVec3d>(_vec0, _vec1);
    fwVec3d pThis;
    if(getClosestPoints(_line, line,pThis,_point) == false) return false;
    fwVec3d tmp = _point-pThis;
    double length = vecLength(tmp);
    if(length>_radius) return false;
    return true;

}

//------------------------------------------------------------------------------

bool intersect( const fwLine& _line, const fwVec3d &_v1,  const fwVec3d &_v2, const fwVec3d &_v3, fwVec3d &_point, fwVec3d &_barycentric, bool& _front) {

    SLM_TRACE_FUNC();
    _barycentric = (_v1 + _v2 + _v3)/3.;
    fwVec3d v01 = _v2 - _v1;
    fwVec3d v12 = _v3 - _v2;
    fwVec3d v20 = _v1 - _v3;

    fwPlane plane = getPlane(_v1, _v2, _v3);

    fwVec3d v;
    v[0] = 0.0F;
    v[1] = 0.0F;
    v[2] = 1.0F;

    const fwVec3d& normal = getNormal(plane);
    _front = (float)(dot(normal,v ))>=0.0F ? true : false;
    if(intersect(plane, _line, _point)==false) return false;

    if((float)(dot(normal, cross(v01, _point-_v1)))<0.0F) return false;
    if((float)(dot(normal, cross(v12, _point-_v2)))<0.0F) return false;
    if((float)(dot(normal, cross(v20, _point-_v3)))<0.0F) return false;
    return true;
}
}
