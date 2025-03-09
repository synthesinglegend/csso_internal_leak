#include "../../global_includes.hpp"
#include "../../New_Amsterdam.hpp"
#include "../config_vars.hpp"
#include <../nlohmann/json.hpp> 

using json = nlohmann::json;

class c_menu {
public:

    void draw_menu();

    void __stdcall ImGui_deviceobjects(IDirect3DDevice9* device) {
        if (hooked::window) {
            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }

    void __stdcall ImGui_objectinvalidation() {
        ImGui_ImplDX9_InvalidateDeviceObjects();
    }

    void __stdcall ImGui_stylesetup(IDirect3DDevice9* device) {
        ImGui_ImplDX9_Init(hooked::window, device);
        ImGuiStyle& style = ImGui::GetStyle();

        style.Alpha = 1.0f;
        style.WindowPadding = ImVec2(10, 10);
        style.WindowMinSize = ImVec2(16, 16);
        style.WindowRounding = 5.0f;
        style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
        style.ChildWindowRounding = 2.0f;
        style.FramePadding = ImVec2(4, 3);  
        style.FrameRounding = 3.0f;
        style.ItemSpacing = ImVec2(10, 10);
        style.ItemInnerSpacing = ImVec2(8, 8);
        style.TouchExtraPadding = ImVec2(0, 0);
        style.IndentSpacing = 21.0f;
        style.ColumnsMinSpacing = 6.0f;
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 10.0f;
        style.GrabMinSize = 10.0f;
        style.GrabRounding = 3.0f;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.DisplayWindowPadding = ImVec2(22, 22);
        style.DisplaySafeAreaPadding = ImVec2(4, 4);
        style.AntiAliasedLines = true;
        style.AntiAliasedShapes = true;
        style.CurveTessellationTol = 1.f;


        ImVec4* colors = ImGui::GetStyle().Colors;


        // Общие цвета
        colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f); // Светлый текст (почти белый)
        colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.00f); // Отключенный текст
        colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.95f); // Темный фон окна
        colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.90f); // Фон попапов
        colors[ImGuiCol_Border] = ImVec4(0.2f, 0.2f, 0.2f, 0.80f); // Мягкие границы
        colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.00f); // Тень границ

        // Фреймы и кнопки
        colors[ImGuiCol_ChildWindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f); // Фон дочерних окон
        colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f); // Фон фреймов
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Подсвеченные фреймы
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f); // Активные фреймы
        colors[ImGuiCol_Button] = ImVec4(0.8f, 0.2f, 0.6f, 1.00f); // Кнопка (неон)
        colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.4f, 0.8f, 1.00f); // Подсвеченные кнопки
        colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.2f, 0.6f, 1.00f); // Активные кнопки

        // Заголовки и разделители
        colors[ImGuiCol_Header] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f); // Фон заголовков
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Подсвеченные заголовки
        colors[ImGuiCol_HeaderActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f); // Активные заголовки
        colors[ImGuiCol_Separator] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f); // Разделители
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f); // Подсвеченные разделители
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.00f); // Активные разделители

        // Скроллбары и захваты
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Фон скроллбара
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); // Захват скроллбара
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.00f); // Подсвеченный захват
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f); // Активный захват

        // Плоты и графики
        colors[ImGuiCol_PlotLines] = ImVec4(0.8f, 0.2f, 0.6f, 1.00f); // Линии графиков
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4f, 0.8f, 1.00f); // Подсвеченные линии графиков
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.8f, 0.2f, 0.6f, 1.00f); // Гистограмма
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.4f, 0.8f, 1.00f); // Подсвеченная гистограмма

        // Другие элементы
        colors[ImGuiCol_CloseButton] = ImVec4(0.8f, 0.2f, 0.6f, 1.00f); // Кнопка закрытия
        colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.0f, 0.4f, 0.8f, 1.00f); // Подсвеченная кнопка закрытия
        colors[ImGuiCol_HotkeyOutline] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f); // Контур горячих клавиш

        ImGui_deviceobjects(device);
    }

    void ImGui_fontcreation() {
        ImGui::CreateContext();
        //menu_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 12);
        menu_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 12);
    }

    void __stdcall end_present(IDirect3DDevice9* device) {
        if (menu_opened) {
            if (ImGui::GetStyle().Alpha > 1.f)
                ImGui::GetStyle().Alpha = 1.f;
            else if (ImGui::GetStyle().Alpha != 1.f)
                ImGui::GetStyle().Alpha += 0.05f;
        }

        ImGui::Render();

        state_block->Apply();
        state_block->Release();
    }

    void __stdcall pre_render(IDirect3DDevice9* device) {
        D3DVIEWPORT9 d3d_viewport;
        device->GetViewport(&d3d_viewport);

        device->CreateStateBlock(D3DSBT_ALL, &state_block);
        state_block->Capture();

        device->SetVertexShader(nullptr);
        device->SetPixelShader(nullptr);
        device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

        device->SetRenderState(D3DRS_LIGHTING, FALSE);
        device->SetRenderState(D3DRS_FOGENABLE, FALSE);
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

        device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
        device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
        device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

        device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
        device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

        device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
        device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

        device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
        device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
    }

    void save_settings() {
        json j;
        j["aim"] = vars.aim;
        j["saim"] = vars.saim;
        j["autofire"] = vars.autofire;
        j["norecoil"] = vars.norecoil;
        j["aimfov"] = vars.aimfov;
        j["esp"] = vars.esp;
        j["esp_name"] = vars.esp_name;
        j["esp_box"] = vars.esp_box;
        j["esp_healthbar"] = vars.esp_healthbar;
        j["esp_skeleton"] = vars.esp_skeleton;
        j["esp_flags"] = vars.esp_flags;
        j["esp_byaw"] = vars.esp_byaw;
        j["bhop_e"] = vars.bhop_e;
        j["faststop"] = vars.faststop;
        j["misc_moonwalk"] = vars.misc_moonwalk;
        j["antiaim"] = vars.antiaim;
        j["esp_nosmoke"] = vars.esp_nosmoke;
        j["esp_noflash"] = vars.esp_noflash;
        j["chams_self"] = vars.chams_self;
        j["chams_modifyc"] = vars.chams_modifyc;
        j["smooth"] = vars.smooth;

        j["hidden_color"] = { vars.hidden_color[0], vars.hidden_color[1], vars.hidden_color[2] };
        j["visible_color"] = { vars.visible_color[0], vars.visible_color[1], vars.visible_color[2] };

        j["fakelag"] = vars.fakelag;
        j["forcevars"] = vars.forcevars;
        j["chams_invisible"] = vars.chams_invisible;
        j["chams_visible"] = vars.chams_visible;

        std::ofstream file("config.json");
        file << j.dump(4); 
        file.close();
    }

    void load_settings() {
        std::ifstream file("config.json");
        if (file.is_open()) {
            json j;
            file >> j;

            vars.aim = j["aim"];
            vars.saim = j["saim"];
            vars.autofire = j["autofire"];
            vars.norecoil = j["norecoil"];
            vars.aimfov = j["aimfov"];
            vars.esp = j["esp"];
            vars.esp_name = j["esp_name"];
            vars.esp_box = j["esp_box"];
            vars.esp_healthbar = j["esp_healthbar"];
            vars.esp_skeleton = j["esp_skeleton"];
            vars.esp_flags = j["esp_flags"];
            vars.esp_byaw = j["esp_byaw"];
            vars.bhop_e = j["bhop_e"];
            vars.faststop = j["faststop"];
            vars.misc_moonwalk = j["misc_moonwalk"];
            vars.antiaim = j["antiaim"];
            vars.esp_nosmoke = j["esp_nosmoke"];
            vars.esp_noflash = j["esp_noflash"];
            vars.chams_self = j["chams_self"];
            vars.chams_modifyc = j["chams_modifyc"];
            vars.smooth = j["smooth"];

            vars.hidden_color[0] = j["hidden_color"][0];
            vars.hidden_color[1] = j["hidden_color"][1];
            vars.hidden_color[2] = j["hidden_color"][2];
            vars.visible_color[0] = j["visible_color"][0];
            vars.visible_color[1] = j["visible_color"][1];
            vars.visible_color[2] = j["visible_color"][2];

            vars.fakelag = j["fakelag"];
            vars.forcevars = j["forcevars"];
            vars.chams_invisible = j["chams_invisible"];
            vars.chams_visible = j["chams_visible"];

            file.close();
        }
    }

    void __stdcall post_render() {
        ImGui_ImplDX9_NewFrame();
    }

    IDirect3DStateBlock9* state_block;
    ImFont* menu_font;
    bool menu_opened = false;
};
inline std::unique_ptr<c_menu> g_menu = std::make_unique<c_menu>();