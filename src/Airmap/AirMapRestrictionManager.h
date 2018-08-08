/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "LifetimeChecker.h"
#include "AirspaceRestrictionProvider.h"
#include "AirMapSharedState.h"
#include "QGCGeoBoundingCube.h"

#include <QList>
#include <QGeoCoordinate>

#include "airmap/geometry.h"
#include "airmap/airspaces.h"

/**
 * @file AirMapRestrictionManager.h
 * Class to download polygons from AirMap
 */

class AirMapRestrictionManager : public AirspaceRestrictionProvider, public LifetimeChecker
{
    Q_OBJECT
public:
    AirMapRestrictionManager            (AirMapSharedState& shared);
    QmlObjectListModel* polygons        () override { return &_polygons; }
    QmlObjectListModel* circles         () override { return &_circles; }
    void                setROI          (const QGCGeoBoundingCube &roi, bool reset = false) override;

signals:
    void error                          (const QString& what, const QString& airmapdMessage, const QString& airmapdDetails);

private:
    void            _requestRestrictions(const QGCGeoBoundingCube& roi);
    void            _addPolygonToList   (const airmap::Geometry::Polygon& polygon, const QColor color);
    QColor          _getColor           (const airmap::Airspace::Type type);

    enum class State {
        Idle,
        RetrieveItems,
    };

    AirMapSharedState&  _shared;
    QGCGeoBoundingCube  _lastROI;
    State               _state = State::Idle;
    QmlObjectListModel  _polygons;
    QmlObjectListModel  _circles;
};

