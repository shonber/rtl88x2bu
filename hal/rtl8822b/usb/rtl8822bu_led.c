/******************************************************************************
 *
 * Copyright(c) 2015 - 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#define _RTL8822BU_LED_C_

#include <drv_types.h>		/* PADAPTER */
#include <hal_data.h>		/* PHAL_DATA_TYPE */
#include <hal_com_led.h>	/* PLED_USB */
#include "../../hal_halmac.h"


/*
 * =============================================================================
 * LED object.
 * =============================================================================
 */


/*
 * =============================================================================
 * Prototype of protected function.
 * =============================================================================
 */

/*
 * =============================================================================
 * LED routines.
 * =============================================================================
 */

/*
 * Description:
 * Turn on LED according to LedPin specified.
 */
static void
SwLedOn_8822BU(
	PADAPTER		padapter,
	PLED_USB		pLed
)
{
	u8	LedCfg;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	if (RTW_CANNOT_RUN(padapter))
		return;

	if (RT_GetInterfaceSelection(padapter) == INTF_SEL2_MINICARD ||
	    RT_GetInterfaceSelection(padapter) == INTF_SEL3_USB_Solo ||
	    RT_GetInterfaceSelection(padapter) == INTF_SEL4_USB_Combo) {


	} else {
                //pLed->LedPin = LED_PIN_LED2;
		switch (pLed->LedPin) {
		case LED_PIN_GPIO0:
			break;

        case LED_PIN_LED0:
        case LED_PIN_LED1:
		case LED_PIN_LED2:
			rtw_halmac_pinmux_wl_led_sw_ctrl(adapter_to_dvobj(padapter), 1);
			break;

		default:
			break;
		}
	}

	pLed->bLedOn = _TRUE;
}

/*
 *	Description:
 *		Turn off LED according to LedPin specified.
 *   */
static void
SwLedOff_8822BU(
	PADAPTER		padapter,
	PLED_USB		pLed
)
{
	u8	LedCfg;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	if (RTW_CANNOT_RUN(padapter))
		return;

	if (RT_GetInterfaceSelection(padapter) == INTF_SEL2_MINICARD ||
	    RT_GetInterfaceSelection(padapter) == INTF_SEL3_USB_Solo ||
	    RT_GetInterfaceSelection(padapter) == INTF_SEL4_USB_Combo) {

	} else {
                //pLed->LedPin = LED_PIN_LED2;
		switch (pLed->LedPin) {
		case LED_PIN_GPIO0:
			break;

        case LED_PIN_LED0:
		case LED_PIN_LED1:
		case LED_PIN_LED2:
			rtw_halmac_pinmux_wl_led_sw_ctrl(adapter_to_dvobj(padapter), 0);
			break;

		default:
			break;
		}
	}

	pLed->bLedOn = _FALSE;
}

void swledon(PADAPTER padapter, PLED_USB pLed)
{
	u8 LedCfg;
	PHAL_DATA_TYPE pHalData = GET_HAL_DATA(padapter);

	if (RTW_CANNOT_RUN(padapter))
		return;

	pLed->bLedOn = _TRUE;
}


/*
 * Description:
 * Turn off LED according to LedPin specified.
 */
void swledoff(PADAPTER padapter, PLED_USB pLed)
{
	u8 LedCfg;
	PHAL_DATA_TYPE pHalData = GET_HAL_DATA(padapter);

	if (RTW_CANNOT_RUN(padapter))
		goto exit;

exit:
	pLed->bLedOn = _FALSE;
}

/*
 * =============================================================================
 * Interface to manipulate LED objects.
 * =============================================================================
 */

/*
 * =============================================================================
 * Default LED behavior.
 * =============================================================================
 */

/*
 * Description:
 * Initialize all LED_871x objects.
 */
void rtl8822bu_initswleds(PADAPTER padapter)
{
	struct led_priv *pledpriv = &(padapter->ledpriv);

	pledpriv->LedControlHandler = LedControlUSB;

	if (IS_HARDWARE_TYPE_8822B(padapter)) {
		pledpriv->SwLedOn = SwLedOn_8822BU;
		pledpriv->SwLedOff = SwLedOff_8822BU;
	}

	InitLed(padapter, &(pledpriv->SwLed0), LED_PIN_LED0);

	InitLed(padapter, &(pledpriv->SwLed1), LED_PIN_LED1);

	InitLed(padapter, &(pledpriv->SwLed2), LED_PIN_LED2);

	rtw_halmac_pinmux_set_func(adapter_to_dvobj(padapter), HALMAC_GPIO_FUNC_WL_LED);
	rtw_halmac_pinmux_wl_led_mode(adapter_to_dvobj(padapter), HALMAC_WLLED_MODE_SW_CTRL);

}

/*
 * Description:
 * DeInitialize all LED_819xUsb objects.
 */
void rtl8822bu_deinitswleds(PADAPTER padapter)
{
	struct led_priv	*ledpriv = &(padapter->ledpriv);

	DeInitLed(&(ledpriv->SwLed0));
	DeInitLed(&(ledpriv->SwLed1));
	DeInitLed(&(ledpriv->SwLed2));

}
