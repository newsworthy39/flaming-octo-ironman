/*
 * DataVisualization.cpp
 *
 *  Created on: 06/06/2015
 *      Author: gandalf
 */

#include <scenes/DataVisualization.h>

namespace scenes {

DataVisualization::DataVisualization(const std::string host, int port) :Dashboard(host, port){
    // this->SetAnimator(animators::StopAndWaitAnimator(30)
    this->SetBasepath("visualization"); //=> makes it into /view/visualization-$messageid
}

DataVisualization::~DataVisualization() {
    // TODO Auto-generated destructor stub
}

void DataVisualization::onDataUpdate(const json11::Json & data) {

}


} /* namespace scenes */
