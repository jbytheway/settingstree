#ifndef SETTINGSTREE__SETTINGS_CALLBACK_HPP
#define SETTINGSTREE__SETTINGS_CALLBACK_HPP

#include <string>

namespace settingsTree {

class Leaf;

class settings_callback {
  public:
    template<typename T>
    std::string settingAlteringCallback(Leaf* altering, T newValue);
};

}

#endif // SETTINGSTREE__SETTINGS_CALLBACK_HPP

