#ifndef SETTINGSTREE__SETTINGS_CALLBACK_HPP
#define SETTINGSTREE__SETTINGS_CALLBACK_HPP

#include <string>

namespace settingsTree {

class Leaf;
class Node;

class settings_callback {
  public:
    template<typename T>
    std::string settingAlteringCallback(Leaf* altering, T newValue);
    virtual void settingAlteredCallback(Node* altered) = 0;
  protected:
    settings_callback() {}
    settings_callback(settings_callback const&) {}
    settings_callback& operator=(settings_callback const&) { return *this; }
    virtual ~settings_callback() = 0;
};

}

#endif // SETTINGSTREE__SETTINGS_CALLBACK_HPP

