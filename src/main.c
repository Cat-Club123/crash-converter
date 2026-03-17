#include <wups.h>
#include <vpad/input.h>
#include <coreinit/debug.h>

WUPS_PLUGIN_NAME("Crash Combo Plugin");
WUPS_PLUGIN_DESCRIPTION("Trigger debug crash with button combo");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("You");

#define COMBO (VPAD_BUTTON_L | VPAD_BUTTON_R | VPAD_BUTTON_DOWN)

static bool awaitingConfirm = false;

void onCrashTrigger() {
    OSFatal("Manual crash triggered for debugging");
}

void checkCombo(VPADStatus *status) {
    if ((status->trigger & COMBO) == COMBO) {
        awaitingConfirm = true;
    }

    if (awaitingConfirm) {
        if (status->trigger & VPAD_BUTTON_A) {
            onCrashTrigger();
        } else if (status->trigger & VPAD_BUTTON_B) {
            awaitingConfirm = false;
        }
    }
}

WUPS_MAIN_ARGS(int argc, char **argv) {}

DECL_FUNCTION(void, VPADRead_hook, VPADChan chan, VPADStatus *status, uint32_t count, int32_t *error) {
    real_VPADRead_hook(chan, status, count, error);
    if (chan == 0 && count > 0 && status) {
        checkCombo(status);
    }
}

WUPS_MUST_REPLACE(VPADRead_hook, WUPS_LOADER_LIBRARY_VPAD, VPADRead);
