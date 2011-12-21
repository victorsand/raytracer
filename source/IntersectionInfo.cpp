#include "IntersectionInfo.h"

IntersectionInfo::IntersectionInfo()
    : t_(0.0f), point_(Point3f()), normal_(Vector3f()), hitTest_(miss()) {}

IntersectionInfo::IntersectionInfo(float _t,
                                   Point3f _point,
                                   Vector3f _normal,
                                   HitTest _hitTest
                                   )
                                   :
                                   t_(_t),
                                   point_(_point),
                                   normal_(_normal),
                                   hitTest_(_hitTest) {}

IntersectionInfo::IntersectionInfo(const IntersectionInfo &_i)
                                   : 
                                   t_(_i.t()),
                                   point_(_i.point()), 
                                   normal_(_i.normal()), 
                                   hitTest_(_i.hitTest()) {}