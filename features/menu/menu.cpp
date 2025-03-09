#include "menu.hpp"
#include "../config_vars.hpp"
#include "../../dependencies/imgui/imgui.h"

inline c_vars vars;

void c_menu::draw_menu() {
    static int selected_tab = 0;

    if (!menu_opened) return;

    auto& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.0f); // Светлый текст
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Отключенный текст

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.95f); // Темный фон окна
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.90f); // Фон попапов
    style.Colors[ImGuiCol_Border] = ImVec4(0.2f, 0.2f, 0.2f, 0.80f); // Мягкие границы

    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f); // Фон дочерних окон
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f); // Фон фреймов
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Подсвеченные фреймы
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f); // Активные фреймы

    style.Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.2f, 0.6f, 1.00f); // Кнопка (неон)
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.4f, 0.8f, 1.00f); // Подсвеченные кнопки
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.2f, 0.6f, 1.00f); // Активные кнопки

    style.Colors[ImGuiCol_Header] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f); // Фон заголовков
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Подсвеченные заголовки
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f); // Активные заголовки

    style.Colors[ImGuiCol_Separator] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f); // Разделители
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f); // Подсвеченные разделители
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.00f); // Активные разделители

    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Фон скроллбара
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); // Захват скроллбара
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.00f); // Подсвеченный захват
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f); // Активный захват

    ImGui::SetNextWindowSize(ImVec2(600, 650), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2(1000, 1000));

    if (ImGui::Begin("*removed*", &menu_opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar)) {
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 header_start = ImGui::GetWindowPos();
        ImVec2 header_end = ImVec2(header_start.x + window_size.x, header_start.y + 41);
        ImGui::GetWindowDrawList()->AddRectFilled(header_start, header_end, ImColor(20, 20, 20), 5.0f);

        ImGui::SetCursorPos(ImVec2(15, 10));
        ImGui::PushFont(menu_font);
        ImGui::Text("*removed*");
        ImGui::PopFont();

        ImGui::Dummy(ImVec2(0, 10));
        float tab_width = window_size.x / 3.0f - 10.0f;

        if (ImGui::ButtonT("Aimbot", ImVec2(tab_width, 35), selected_tab, 0, true)) selected_tab = 0;
        ImGui::SameLine();
        if (ImGui::ButtonT("Visuals", ImVec2(tab_width, 35), selected_tab, 1, true)) selected_tab = 1;
        ImGui::SameLine();
        if (ImGui::ButtonT("Miscellaneous", ImVec2(tab_width, 35), selected_tab, 2, true)) selected_tab = 2;

        ImVec2 content_size = ImVec2(window_size.x - 40, window_size.y - 100);
        ImGui::SetCursorPos(ImVec2(20, 80));

        switch (selected_tab) {
        case 0: // Aimbot Tab
            ImGui::BeginChild("Aimbot Settings", content_size, true);
            //ImGui::Dummy(ImVec2(0, 2));

            ImGui::Text("Aimbot Settings");
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 2));

            ImGui::Indent(10);
            ImGui::Checkbox("Enable Aimbot", &vars.aim);
            ImGui::SliderInt("Aim Bone", &vars.bone, 0, 12, "%.f bone");
            ImGui::SliderFloat("Smoothing", &vars.smooth, 0.0f, 100.0f, "%.1f%%");
            ImGui::Checkbox("Silent Aim", &vars.saim);
            ImGui::Checkbox("Auto Fire", &vars.autofire);
            ImGui::Checkbox("Nullify Recoil", &vars.norecoil);
            ImGui::SliderFloat("FOV", &vars.aimfov, 0.0f, 180.0f, "%.1f degrees");
            ImGui::Unindent(10);

            ImGui::EndChild();
            break;

        case 1: // Visuals Tab
            ImGui::BeginChild("Visuals Settings", content_size, true);
            //ImGui::Dummy(ImVec2(0, 2));

            ImGui::Text("Player ESP");
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 2));

            ImGui::Indent(10);
            ImGui::Checkbox("Enable ESP", &vars.esp);
            ImGui::Checkbox("Display Name", &vars.esp_name);
            ImGui::Checkbox("Display Boxes", &vars.esp_box);
            ImGui::Checkbox("Healthbar", &vars.esp_healthbar);
            ImGui::Checkbox("Skeleton", &vars.esp_skeleton);
            ImGui::Checkbox("Flags", &vars.esp_flags);
            ImGui::Checkbox("Body Yaw", &vars.esp_byaw);
            ImGui::Dummy(ImVec2(0, 10));

            ImGui::Checkbox("Enable Chams", &vars.chams_self);
            ImGui::Checkbox("Invisible Enemies", &vars.chams_invisible);
            ImGui::Checkbox("Visible Enemies", &vars.chams_visible);
            ImGui::Checkbox("Customize Chams Colors", &vars.chams_modifyc);

            if (vars.chams_modifyc) {
                ImGui::Text("Material Colors");
                ImGui::ColorEdit4("Hidden Color", vars.hidden_color, ImGuiColorEditFlags_HEX);
                ImGui::ColorEdit4("Visible Color", vars.visible_color, ImGuiColorEditFlags_HEX);
            }

            ImGui::Unindent(10);

            ImGui::Dummy(ImVec2(0, 10));
            ImGui::Text("World Settings");
            ImGui::Separator();

            ImGui::Indent(10);
            ImGui::Checkbox("Nullify Flashbang", &vars.esp_noflash);
            ImGui::Checkbox("Remove Smoke", &vars.esp_nosmoke);
            ImGui::Unindent(10);

            ImGui::EndChild();
            break;

        case 2: // Miscellaneous Tab
            ImGui::BeginChild("Miscellaneous Settings", content_size, true);
            //ImGui::Dummy(ImVec2(0, 2));

            ImGui::Text("Miscellaneous Settings");
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 2));

            ImGui::Indent(10);
            ImGui::Checkbox("Bunny Hop", &vars.bhop_e);
            ImGui::Checkbox("Air Strafe", &vars.airstrafe);
            ImGui::Checkbox("Quick Stop", &vars.faststop);
            ImGui::Checkbox("Moonwalk", &vars.misc_moonwalk);
            ImGui::Checkbox("Bypass Cvars", &vars.forcevars);
            ImGui::Checkbox("Fakelag (Beta)", &vars.fakelag);

            if (vars.fakelag) {
                ImGui::SameLine();
                ImGui::SliderInt("Fakelag Amount", &vars.fakelagamount, 0, 21, "%.1f ticks");
            }

            ImGui::Checkbox("Anti-Aim (Beta)", &vars.antiaim);
            if (vars.antiaim) {
                ImGui::SliderFloat("Anti-Aim Add", &vars.antiaimdeg, -180.0f, 180.0f, "%.1f degrees");
                ImGui::SliderFloat("Anti-Aim Fake", &vars.antiaimdeg2, -180.0f, 180.0f, "%.1f degrees");
            }

            ImGui::Dummy(ImVec2(0, 10));

            if (ImGui::Button("Load Settings", ImVec2(130, 30))) {
                load_settings();
            }

            ImGui::SameLine();
            if (ImGui::Button("Save Settings", ImVec2(130, 30))) {
                save_settings();
            }

            ImGui::Unindent(10);

            ImGui::EndChild();
            break;

        default:
            break;
        }
    }

    ImGui::End();
}
