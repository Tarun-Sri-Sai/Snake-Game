#include "window_manager.hpp"

WindowManager::WindowManager() : m_stack() {}

void WindowManager::listen() {
    if (m_stack.empty()) {
        return;
    }

    m_stack.top().get()->listen();
}

void WindowManager::update(float t_deltaTime) {
    if (m_stack.empty()) {
        return;
    }

    m_stack.top().get()->update(t_deltaTime);
}

void WindowManager::draw() {
    if (m_stack.empty()) {
        return;
    }

    m_stack.top().get()->draw();
}

void WindowManager::open(std::unique_ptr<Window> t_window, bool inplace) {
    if (!inplace && !m_stack.empty()) {
        m_stack.pop();
    }

    m_stack.push(std::move(t_window));
}
