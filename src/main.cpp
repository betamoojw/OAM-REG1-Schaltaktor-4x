#include "OpenKNX.h"
#include "Logic.h"
#include "FileTransferModule.h"
#include "SwitchActuatorModule.h"


void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);

    if (openknx.ledFunctions.useDefaultFunction())
    {
        openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3), OPENKNX_LEDFUNC_SWA_STATUS+1); 
        openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2), OPENKNX_LEDFUNC_SWA_STATUS+2); 
        openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO1), OPENKNX_LEDFUNC_SWA_STATUS+3);
    }

    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxSwitchActuatorModule);
    
    openknx.addModule(9, openknxFileTransferModule);
    openknx.setup();

    openknx.func3Button.onShortClick([]()
    {
        openknxSwitchActuatorModule.doSwitchChannel(0, !openknxSwitchActuatorModule.getChannelStatus(0), true);
    });

    openknx.func2Button.onShortClick([]()
    {
        openknxSwitchActuatorModule.doSwitchChannel(1, !openknxSwitchActuatorModule.getChannelStatus(1), true);
    });

    openknx.func1Button.onShortClick([]()
    {
        openknxSwitchActuatorModule.doSwitchChannel(2, !openknxSwitchActuatorModule.getChannelStatus(2), true);
    });
}

void loop()
{
    openknx.loop();
    if(knx.configured())
    {
    }
    else
    {
        openknx.ledFunctions.get(OPENKNX_LEDFUNC_SWA_STATUS+3)->color(OpenKNX::Led::Color::Yellow);
        openknx.ledFunctions.get(OPENKNX_LEDFUNC_SWA_STATUS+3)->on();

        openknx.ledFunctions.get(OPENKNX_LEDFUNC_SWA_STATUS+2)->color(OpenKNX::Led::Color::Yellow);
        openknx.ledFunctions.get(OPENKNX_LEDFUNC_SWA_STATUS+2)->on();

        openknx.ledFunctions.get(OPENKNX_LEDFUNC_SWA_STATUS+1)->color(OpenKNX::Led::Color::Yellow);
        openknx.ledFunctions.get(OPENKNX_LEDFUNC_SWA_STATUS+1)->on();
    }
}