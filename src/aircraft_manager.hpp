#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    using AircraftList     = std::vector<std::unique_ptr<Aircraft>>;
    AircraftList aircrafts = {};

public:
    void add(std::unique_ptr<Aircraft> aircraft);

    void move() override;

    friend Aircraft;
};