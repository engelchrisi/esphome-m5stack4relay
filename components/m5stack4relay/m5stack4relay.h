#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5stack4relay {

static constexpr uint8_t UNIT_4RELAY_CONFIG_REG = 0X10;
static constexpr uint8_t UNIT_4RELAY_RELAY_REG = 0X11;

enum class RelayBit : uint8_t {
  RELAY1 = 3,
  RELAY2 = 2,
  RELAY3 = 1,
  RELAY4 = 0,
  NONE = 255
};

// ====================================================================================

class M5Relay4Control : public i2c::I2CDevice, public Component {
 public:
  void setup() override;
  void dump_config() override;

  bool set_relay(RelayBit bit, bool state);
  bool set_relays(RelayBit bit0, bool state0, RelayBit bit1, bool state1);
  bool get_relay_state(RelayBit bit);
  
 protected:
  uint8_t get_relay_states_();
  bool has_been_setup_{false};
};


}  // namespace m5stack4relay
}  // namespace esphome
