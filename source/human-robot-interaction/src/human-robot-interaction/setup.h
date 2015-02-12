/**
 * Author: Aravinth Panchadcharam
 * Email: me@aravinth.info
 * Date: 12/02/15.
 * Project: Gesture Recogntion for Human-Robot Interaction
 */

#ifndef __human_robot_interaction__setup__
#define __human_robot_interaction__setup__

#include <stdio.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

static std::string configFileName = "/Users/aravinth/hri.conf";
static boost::property_tree::ptree pt;

template<typename T> T getConfigValue(std::string attr)
{
    boost::property_tree::read_json(configFileName, pt);
    return pt.get<T>(attr);
}

#endif
