#include "draw.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <algorithm>
#include "My_font/zh_Font.h"
#include "My_font/fontawesome-brands.h"
#include "My_font/fontawesome-regular.h"
#include "My_font/fontawesome-solid.h"
#include "My_font/gui_icon.h"
#include "My_icon/pic_ZhenAiKun_png.h"

struct ClassInfo {
    std::unordered_map<std::string, std::string> members;
};
std::unordered_map<std::string, ClassInfo> classDatabase;
std::string sdkParseResult;
bool showSdkParserWindow = false;
char sdkFilePath[256] = "";
char ruleFilePath[256] = "";
char outputFilePath[256] = "result.txt";
bool isParsing = false;
float parseProgress = 0.0f;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void BuildClassDatabase(const std::string& sdkContent) {
    classDatabase.clear();
    std::istringstream iss(sdkContent);
    std::string line;
    std::string currentClass;
    
    while (std::getline(iss, line)) {
        line = trim(line);
        if (line.find("Class: ") == 0) {
            currentClass = trim(line.substr(7));
            continue;
        }
        
        if (!currentClass.empty() && line.find("Offset: 0x") != std::string::npos) {
            size_t typeEnd = line.find_first_of(" \t");
            if (typeEnd == std::string::npos) continue;
            
            std::string type = line.substr(0, typeEnd);
            std::string name = line.substr(typeEnd + 1);
            
            size_t nameEnd = name.find_first_of(" \t;");
            if (nameEnd != std::string::npos) name = name.substr(0, nameEnd);
            
            size_t offsetPos = line.find("Offset: 0x");
            if (offsetPos != std::string::npos) {
                std::string offset = line.substr(offsetPos + 8);
                offset = trim(offset.substr(0, offset.find_first_of(" \t\n\r")));
                classDatabase[currentClass].members[name] = offset;
            }
        }
    }
}

std::string ProcessRules(const std::string& ruleContent) {
    std::ostringstream result;
    std::istringstream iss(ruleContent);
    std::string line;
    
    while (std::getline(iss, line)) {
        line = trim(line);
        if (line.empty() || line.find("//") == 0) {
            result << line << "\n";
            continue;
        }
        
        size_t pos1 = line.find('#');
        size_t pos2 = line.find('#', pos1 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string funcName = trim(line.substr(0, pos1));
            std::string className = trim(line.substr(pos1 + 1, pos2 - pos1 - 1));
            std::string memberName = trim(line.substr(pos2 + 1));
            
            className = trim(className);
            if (className.find("Class: ") == 0) className = className.substr(7);
            memberName = trim(memberName);
            if (memberName.back() == ';') memberName.pop_back();
            
            auto classIt = classDatabase.find(className);
            if (classIt != classDatabase.end()) {
                auto memberIt = classIt->second.members.find(memberName);
                if (memberIt != classIt->second.members.end()) {
                    result << funcName << "\t\t" << memberIt->second << "\n";
                    continue;
                }
            }
        }
        result << line << "\n";
    }
    return result.str();
}

// 保持原有的其他函数不变...

void Layout_tick_UI(bool *main_thread_flag) {
    static bool show_draw_Line = false;
    static bool show_demo_window = false;
    static bool show_another_window = false;
    { 
        static float f = 0.0f;
        static int counter = 0;
        static int style_idx = 0;
        static ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        ImGui::Begin("搞批(Symbol chain)1.45", main_thread_flag);
        if (::permeate_record_ini) {
            ImGui::SetWindowPos({LastCoordinate.Pos_x, LastCoordinate.Pos_y});
            ImGui::SetWindowSize({LastCoordinate.Size_x, LastCoordinate.Size_y});
            permeate_record_ini = false;   
        }
        if (ImGui::Button("SDK解析器")) {
            showSdkParserWindow = true;
        }
        
        if (showSdkParserWindow) {
            ImGui::Begin("SDK解析器", &showSdkParserWindow, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::InputText("SDK文件", sdkFilePath, IM_ARRAYSIZE(sdkFilePath));
            ImGui::InputText("规则文件", ruleFilePath, IM_ARRAYSIZE(ruleFilePath));
            ImGui::InputText("输出文件", outputFilePath, IM_ARRAYSIZE(outputFilePath));
            
            if (ImGui::Button("解析") && !isParsing) {
                isParsing = true;
                parseProgress = 0.0f;
                std::thread([&]() {
                    std::ifstream sdkFile(sdkFilePath);
                    if (!sdkFile) {
                        sdkParseResult = "无法打开SDK文件";
                        isParsing = false;
                        return;
                    }
                    std::string sdkContent((std::istreambuf_iterator<char>(sdkFile)), std::istreambuf_iterator<char>());
                    parseProgress = 0.3f;
                    BuildClassDatabase(sdkContent);
                    parseProgress = 0.6f;
                    
                    std::ifstream ruleFile(ruleFilePath);
                    if (!ruleFile) {
                        sdkParseResult = "无法打开规则文件";
                        isParsing = false;
                        return;
                    }
                    std::string ruleContent((std::istreambuf_iterator<char>(ruleFile)), std::istreambuf_iterator<char>());
                    parseProgress = 0.8f;
                    sdkParseResult = ProcessRules(ruleContent);
                    parseProgress = 1.0f;
                    
                    std::ofstream outFile(outputFilePath);
                    outFile << sdkParseResult;
                    isParsing = false;
                }).detach();
            }
            
            if (isParsing) {
                ImGui::SameLine();
                ImGui::ProgressBar(parseProgress, ImVec2(100, 20));
            }
            
            if (!sdkParseResult.empty()) {
                ImGui::Separator();
                ImGui::Text("解析结果:");
                ImGui::BeginChild("Result", ImVec2(600, 400), true);
                ImGui::TextUnformatted(sdkParseResult.c_str());
                ImGui::EndChild();
                
                if (ImGui::Button("保存结果")) {
                    std::ofstream outFile(outputFilePath);
                    outFile << sdkParseResult;
                    ImGui::OpenPopup("保存成功");
                }
                
                if (ImGui::BeginPopupModal("保存成功", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    ImGui::Text("结果已保存到: %s", outputFilePath);
                    if (ImGui::Button("确定")) {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
            }
            ImGui::End();
        }
        ImGui::End();
    }
    
    if (show_another_window) {
        ImGui::Begin("另一个窗口", &show_another_window);
        ImGui::Text("另一个窗口的 爱坤!");
        ImGui::Image(Aekun_image.DS, ImVec2(170, 170));
        if (ImGui::Button("关闭这个坤口")) {
            show_another_window = false;
        }
        ImGui::End();
    }
    
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    if (show_draw_Line)
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(0,0),ImVec2(displayInfo.width, displayInfo.height),IM_COL32(255,0,0,255),4);
}