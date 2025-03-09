#pragma once
#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>
#include "interfaces/interfaces.hpp"
#include "../sdk/sdk_includes.hpp"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../dependencies/utils/hook.hpp"
#include "../hooked/hooked.hpp"
#include "utils/renderer.hpp"
#include "math/math.hpp"
#include <memory>
