#include "Library.h"

int library_add(int first, int second) { return first + second; }

int Library::Add(int first, int second) { return first + second; }

Library::X::X(std::string str) : m_str{std::move(str)} {}
std::string Library::X::str() const { return m_str; }
void Library::X::str(std::string str) { m_str = std::move(str); }
