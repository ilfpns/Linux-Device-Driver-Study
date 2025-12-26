#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

static struct gpio_desc *led;

static int my_led_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;

	pr_info("gpio-led: probe");

	led = devm_gpiod_get(dev, NULL, GPIOD_OUT LOW);
	if (IS_ERR(led)) {
		return PTR_ERR(led);
	}

	return 0;
}

static void my_led_remove(struct platform_device *pdev) {
	gpiod_set_value(led, 0);
	pr_info("gpio-led : remove\n");
}

static const struct of_device_id my_led_of_match[] = {
	{ .compatible = "mycompany,gpio-led" },
	{ }
};
MODULE_DEVICE_TABLE(of, my_led_of_match);

static struct platform_driver my_led_driver = {
	.probe = my_led_probe,
	.remove = my_led_remove,
	.driver = {
		.name = "my-gpio-led",
		.of_match_table = my_led_of_match,
	,
};

module_playform_driver(my_led_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");
MODULE_DESCRIPTION("Control LED");

