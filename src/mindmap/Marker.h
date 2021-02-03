#pragma once

#include <string>

class Marker {
   public:
    Marker() = default;

    const std::string& getSymbol() { return m_symbol; }
    void setSymbol(const std::string& _symbol) { m_symbol = _symbol; }

    friend bool operator==(const Marker& lhs, const Marker& rhs) { return lhs.m_symbol == rhs.m_symbol; }
    friend bool operator!=(const Marker& lhs, const Marker& rhs) { return !(lhs.m_symbol == rhs.m_symbol); }

   private:
    friend std::hash<Marker>;
    std::string m_symbol;
};

// See https://en.cppreference.com/w/cpp/utility/hash/operator()
template <>
class std::hash<Marker> {
   public:
    std::size_t operator()(const Marker& _marker) const noexcept { return std::hash<std::string>{}(_marker.m_symbol); }
};