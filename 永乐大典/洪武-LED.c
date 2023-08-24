#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"


void app_main(void)
{printf("hy wu 3\n");//年号：洪武

	int i=1,r=0,g=0,b=0;
	static uint8_t led_io = 0;
	static led_strip_handle_t led_strip;



	//根据LED类型配置外围设备
    //使用GPIO和像素数初始化LED条
    led_strip_config_t strip_config = {
        //.strip_gpio_num = LED_pin,
		.strip_gpio_num =CONFIG_BLINK_GPIO,
        .max_leds = 1, // 板上至少有一个LED
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    // 关闭所有LED以清除所有像素
    led_strip_clear(led_strip);





    //--------------------------主函数---
    while (1) {

    	//切换LED/如果可寻址LED已启用/状态
        if (led_io) {
            // 使用RGB为每种颜色设置从0（0%）到255（100%）的LED像素
            led_strip_set_pixel(led_strip, 0, r, g, b);
            // 刷新条形图以发送数据
            led_strip_refresh(led_strip);
        } else {
            // 关闭所有LED以清除所有像素clear
            led_strip_clear(led_strip);
        }




        //-----------------------------切换LED状态-----------------------------
        led_io = !led_io;

        vTaskDelay(50);
             if(i==1){r=1;g=0;b=0;}
             if(i==2){r=0;g=1;b=0;}
        	 if(i==3){r=0;g=0;b=1;}
             i++;
             if(i==4){i=1;}
    }

}




