#include "sleep_utils.h"
#include "boards_pinout.h"

bool lowPowerModeActive = true;
bool wakeUpFlag = false;

namespace SLEEP_Utils {

    void handle_wakeup() {
        esp_sleep_wakeup_cause_t wakeup_cause = esp_sleep_get_wakeup_cause();
        switch (wakeup_cause) {
            case ESP_SLEEP_WAKEUP_TIMER:
                Serial.print("Woken up by timer (Sending Beacon) \n");
                break;
            case ESP_SLEEP_WAKEUP_EXT1:
                Serial.print("Woken up by EXT1 (GPIO) (Packet Received)\n");
                break;
            default:
                Serial.print("Woken up by unknown reason\n");
                break;
        }
    }

    void wakeUpLoRaPacketReceived() {
        wakeUpFlag = true;
    }

    void setup() {
        if (lowPowerModeActive) {
            pinMode(RADIO_WAKEUP_PIN, INPUT);
            attachInterrupt(digitalPinToInterrupt(RADIO_WAKEUP_PIN), wakeUpLoRaPacketReceived, RISING);
            //LoRa_Utils::wakeRadio();
        }
    }

}