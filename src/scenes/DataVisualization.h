/*
 * DataVisualization.h
 *
 *  Created on: 06/06/2015
 *      Author: gandalf
 */

#ifndef DATAVISUALIZATION_H_
#define DATAVISUALIZATION_H_

#include <scenes/Dashboard.h>
#include <json11/json11.hpp>
#include <SFML/OpenGL.hpp>
#include <interface/DrawablePanel.hpp>
#include <interface/Observable.hpp>

namespace scenes {

class DataVisualization: public Dashboard {
public:
    DataVisualization(const std::string host, int port);
    virtual ~DataVisualization();
    // Get data from dashboard
    void onDataUpdate(const json11::Json & data);
};

} /* namespace scenes */

#endif /* DATAVISUALIZATION_H_ */
