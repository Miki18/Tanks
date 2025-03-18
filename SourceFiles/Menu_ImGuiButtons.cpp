//Here are buttons designs related to Menu state (Menu.h)
#include "../HeaderFiles/Menu.h"

void Menu::DefaultButtonSettings()
{
	style.Colors[ImGuiCol_Button] = ImVec4(0.75f, 0.75f, 0.75f, 0.8f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
}

void Menu::PlayButton(ImVec2 WindowPosition)
{
	DefaultButtonSettings();
	ImGui::SetNextWindowPos(WindowPosition);
	ImGui::Begin("PlayButton", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowSize(ImVec2{ ButtonDefaultXSize, ButtonDefaultYSize });
	if (ImGui::Button("Play", ImVec2{ static_cast<float>(ButtonDefaultXSize * 0.95), static_cast<float>(ButtonDefaultYSize * 0.88) }))
	{
		changeState = true;
	}
	ImGui::End();
}

void Menu::ExitButton(ImVec2 WindowPosition)
{
	DefaultButtonSettings();
	ImGui::SetNextWindowPos(ImVec2{ static_cast<float>(WindowXSize) / 2 - ButtonDefaultXSize / 2, static_cast<float>(WindowYSize) / 2 - ButtonDefaultYSize / 2 });
	ImGui::Begin("ExitButton", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowSize(ImVec2{ ButtonDefaultXSize, ButtonDefaultYSize });
	if (ImGui::Button("Exit", ImVec2{ static_cast<float>(ButtonDefaultXSize * 0.95), static_cast<float>(ButtonDefaultYSize * 0.88) }))
	{
		window.close();
	}
	ImGui::End();
}