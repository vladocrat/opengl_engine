#include "window.h"

Window::Window(int32_t width, int32_t height, const std::string& header)
{
    m_window = glfwCreateWindow(width, height, header.c_str(), nullptr, nullptr);
}

Window::~Window() noexcept
{

}

bool Window::isValid() const noexcept
{
    return m_window;
}

GLFWwindow* Window::obj() const noexcept
{
    return m_window;
}
