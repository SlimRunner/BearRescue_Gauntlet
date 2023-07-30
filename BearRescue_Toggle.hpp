#pragma once

/**
 * @brief Keeps track of the press state of a press switch, so that it can
 * simulate a toggle switch
 *
 */
class Toggle {
private:
  int m_switchState;
  bool m_toggleState;
  int m_pin;

public:
  /**
   * @brief Default constructor is disallowed
   *
   */
  Toggle() = delete;

  /**
   * @brief Construct a new Toggle object with a given initial state
   *
   * @param pin pin id where switch is connected
   */
  Toggle(uint8_t m_pin);

  // default destructor

  /**
   * @brief Determine signal has changed since last call
   *
   * @return true if switch state has changed
   * @return false otherwise
   */
  bool isToggled();

  /**
   * @brief Determine the state of the last update
   *
   * @return true if last update recorded HIGH,
   * @return false otherwise
   */
  bool isHigh();
  
  /**
   * @brief Determine the state of the last update
   *
   * @return true if last update recorded LOW,
   * @return false otherwise
   */
  bool isLow();

  /**
   * @brief Determine the state of the simulated toggle
   *
   * @return true if the toggle would be ON,
   * @return false otherwise
   */
  bool isOn();

  /**
   * @brief Determine the state of the simulated toggle
   *
   * @return true if the toggle would be OFF,
   * @return false otherwise
   */
  bool isOff();
};

Toggle::Toggle(uint8_t pin) : m_pin(pin), m_toggleState(false) {
  m_switchState = digitalRead(m_pin);
}

bool Toggle::isToggled() {
  int newState = digitalRead(m_pin);
  bool changed = m_switchState != newState;
  m_switchState = newState;
  if (changed && newState) {
    m_toggleState = !m_toggleState;
  }
  return changed;
}

bool Toggle::isHigh() { return m_switchState == HIGH; }

bool Toggle::isLow() { return m_switchState == LOW; }

bool Toggle::isOn() { return m_toggleState; }

bool Toggle::isOff() { return !m_toggleState; }
