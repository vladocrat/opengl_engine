#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int32_t width, int32_t height, const std::string& header = "");
    ~Window() noexcept;

    [[nodiscard]] bool isValid() const noexcept;
    [[nodiscard]] GLFWwindow* obj() const noexcept;

private:
    GLFWwindow* m_window { nullptr };
};

