#include <iostream>
#include <vector>
#include <string>

// ImGui & Graphics Headers
#include "ui_lib/imgui.h"
#include "ui_lib/imgui_impl_glfw.h"
#include "ui_lib/imgui_impl_opengl3.h"
#include "ui_lib/GLFW/glfw3.h"

// Your Core Headers
#include "MusicPlayerApplication.hpp"

std::string currentStatus = "Idle - Waiting for user input.";
std::string connectedDeviceStr = "Bluetooth Speaker (Default)";
std::string currentStrategyStr = "Sequential (Default)";

int main() {
    auto application = MusicPlayerApplication::getInstance();
    application->createSongInLibrary("Kesariya", "Arijit Singh", "/music/kesariya.mp3");
    application->createSongInLibrary("Chaiyya Chaiyya", "Sukhwinder Singh", "/music/chaiyya_chaiyya.mp3");
    application->createSongInLibrary("Tum Hi Ho", "Arijit Singh", "/music/tum_hi_ho.mp3");
    application->createSongInLibrary("Jai Ho", "A. R. Rahman", "/music/jai_ho.mp3");
    application->createSongInLibrary("Zinda", "Siddharth Mahadevan", "/music/zinda.mp3");

    application->createPlaylist("Bollywood Vibes");
    application->addSongToPlaylist("Bollywood Vibes", "Kesariya");
    application->addSongToPlaylist("Bollywood Vibes", "Chaiyya Chaiyya");
    application->addSongToPlaylist("Bollywood Vibes", "Tum Hi Ho");
    application->addSongToPlaylist("Bollywood Vibes", "Jai Ho");
    
    application->connectAudioDevice(DeviceType::BLUETOOTH);
    application->selectPlayStrategy(PlayStrategyType::SEQUENTIAL);
    application->loadPlaylist("Bollywood Vibes");

    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(600, 450, "C++ Architecture Engine: Music Player", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::Begin("Streaming Controller Dashboard", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Hardware Output State:");
        ImGui::Text("Connected Device: %s", connectedDeviceStr.c_str());
        ImGui::Text("Active Strategy: %s", currentStrategyStr.c_str());
        ImGui::Separator();

        if (ImGui::Button("Use Bluetooth")) {
            application->connectAudioDevice(DeviceType::BLUETOOTH);
            connectedDeviceStr = "Bluetooth Speaker (Adapter Pattern)";
            currentStatus = "Switched output device context successfully to Bluetooth.";
        }
        ImGui::SameLine();
        if (ImGui::Button("Use Headphones")) {
            application->connectAudioDevice(DeviceType::HEADPHONES);
            connectedDeviceStr = "Wired Headphones (Adapter Pattern)";
            currentStatus = "Switched hardware route to Headphones.";
        }

        ImGui::Spacing();
        ImGui::Separator();

        ImGui::Text("Playback Strategy Modifications:");
        if (ImGui::Button("Sequential Mode")) {
            application->selectPlayStrategy(PlayStrategyType::SEQUENTIAL);
            application->loadPlaylist("Bollywood Vibes");
            currentStrategyStr = "Sequential";
            currentStatus = "Switched strategy context to Sequential.";
        }
        ImGui::SameLine();
        if (ImGui::Button("Shuffle Mode")) {
            application->selectPlayStrategy(PlayStrategyType::RANDOM);
            application->loadPlaylist("Bollywood Vibes");
            currentStrategyStr = "Random (Shuffle)";
            currentStatus = "Switched strategy context to Random Shuffle.";
        }

        ImGui::Spacing();
        ImGui::Separator();

        ImGui::Text("Media Controls:");
        
        if (ImGui::Button("Back Track")) {
            try {
                application->playPreviousTrackInPlaylist();
                currentStatus = "Triggered Previous Track Hook via Strategy Pattern.";
            } catch (const std::exception& e) { currentStatus = e.what(); }
        }
        ImGui::SameLine();
        if (ImGui::Button("Play All Tracks")) {
            try {
                application->playAllTracksInPlaylist();
                currentStatus = "Streaming entire loaded playlist sequentially to console.";
            } catch (const std::exception& e) { currentStatus = e.what(); }
        }
        ImGui::SameLine();
        if (ImGui::Button("Next Track")) {
            try {
                MusicPlayerFacade::getInstance()->playNextTrack();
                currentStatus = "Advanced to next song resource link via Facade.";
            } catch (const std::exception& e) { currentStatus = e.what(); }
        }

        ImGui::Spacing();
        ImGui::Separator();

        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.4f, 1.0f), "Engine Output Log:");
        ImGui::BeginChild("LogWindow", ImVec2(0, 120), true);
        ImGui::TextWrapped("%s", currentStatus.c_str());
        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}