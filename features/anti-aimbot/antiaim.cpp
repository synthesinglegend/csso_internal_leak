#include "antiaim.hpp"
#include "../config_vars.hpp"
#include <interfaces.hpp>

/*
* OOP standarts?  Nah, let it be like this
* P.S this part was not written by me (nightmare__)
* Made (or pasted) by twod1e
*/

double random_float(double min_value, double max_value) {
    // Генерация случайного числа в диапазоне от 0 до 1
    double random = static_cast<double>(rand()) / RAND_MAX;

    // Масштабируем его в нужный диапазон
    return min_value + random * (max_value - min_value);
}

void antiaim_(usercmd* cmd)
{
    if (!vars.antiaim) return;

    auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;

    cmd->viewangles.x = 89.f;


    if (vars.m_packetbool)
    {
        cmd->viewangles.y += vars.antiaimdeg2;
    }
    else
        cmd->viewangles.y += vars.antiaimdeg;
}