#pragma once

#include "aircraft_manager.hpp"

class Airport;
struct AircraftType;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager aircraft_manager;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type);
    std::unique_ptr<Aircraft> create_random_aircraft();

    void create_keystrokes() const;
    void display_help() const;

    void init_airport();
    void init_aircraft_manager();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
