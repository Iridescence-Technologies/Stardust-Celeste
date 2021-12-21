/**
 * @file PlatformLayer.hpp
 * @author Nathan Bourgeois <iridescentrosesfall@gmail.com>
 * @brief Platform Setup Layer
 * @version 0.1
 * @date 2021-12-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <Utilities/Utilities.hpp>

namespace Stardust_Celeste::Core {

struct AppConfig {
    bool headless = false;
};

class PlatformLayer : Singleton {
public:
  PlatformLayer() = default;

  auto initialize(const AppConfig &app) -> void;
  auto terminate() -> void;

  inline static auto Get() -> PlatformLayer & {
    static PlatformLayer ply;
    return ply;
  }

private:
};
} // namespace Stardust_Celeste::Core