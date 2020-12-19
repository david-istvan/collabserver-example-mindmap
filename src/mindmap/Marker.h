#pragma once

class Marker {
   public:
    Marker() = default;
    Marker(const char* _name) : m_name{_name} {}

    const char* getSymbol() { return m_symbol; }
    void setSymbol(const char* _symbol) { m_symbol = _symbol; }

   private:
    const char* m_symbol;
    const char* m_name;
};
