#include "esphome/core/log.h"
#include "m5stack4relay.h"
#include <bitset>

namespace esphome {
namespace m5stack4relay {

static const char *const TAG = "m5stack_4relay.switch";

void M5Relay4Control::dump_config() { 
  ESP_LOGCONFIG(TAG, "M5Stack 4relay switch"); 
  ESP_LOGCONFIG(TAG, "has_been_setup_=%i", has_been_setup_); 
}

void M5Relay4Control::setup() {
  write_byte(UNIT_4RELAY_CONFIG_REG, true);

  ESP_LOGCONFIG(TAG, "Setting up M5STACK4RELAY (0x%02X)...", this->address_);
  uint8_t component_status = get_relay_states_();
  ESP_LOGD(TAG, "Setup Status 0x%02X", component_status);
  has_been_setup_ = true;
}

uint8_t M5Relay4Control::get_relay_states_() {
  uint8_t result;
  this->read_byte(UNIT_4RELAY_RELAY_REG, &result);
  return result;
}

bool M5Relay4Control::get_relay_state(RelayBit bit) {
  const uint8_t org0 = get_relay_states_();
  return (org0 & (1u << (uint8_t) bit)) != 0;
}

bool M5Relay4Control::set_relay(RelayBit bit, bool state) {
  const uint8_t org0 = get_relay_states_();

  uint8_t org= org0;
  if (state) {
    org |= (1u << (uint8_t) bit);
  } else {
    org &= ~(1u << (uint8_t) bit);
  }

  ESP_LOGD(TAG, "set_relay 0x%X => 0x%X", org0, org);  
  return write_byte(UNIT_4RELAY_RELAY_REG, org);
}

bool M5Relay4Control::set_relays(RelayBit bit0, bool state0, RelayBit bit1, bool state1) {
  const uint8_t org0 = get_relay_states_();

  uint8_t org= org0;
  if (state0) {
    org |= (1u << (uint8_t) bit0);
  } else {
    org &= ~(1u << (uint8_t) bit0);
  }
  if (state1) {
    org |= (1u << (uint8_t) bit1);
  } else {
    org &= ~(1u << (uint8_t) bit1);
  }  

  ESP_LOGD(TAG, "set_relays 0x%X => 0x%X", org0, org);  
  return write_byte(UNIT_4RELAY_RELAY_REG, org);
}



}  // namespace m5stack4relay
}  // namespace esphome
