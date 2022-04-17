#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

void AircraftManager::move()
{
    for (auto& aircraft : aircrafts)
    {
        aircraft->move();
    }
    std::remove_if(aircrafts.begin(), aircrafts.end(),
                   [](const auto& aircraft) { return aircraft->finished });
}