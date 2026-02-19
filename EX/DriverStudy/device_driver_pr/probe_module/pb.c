#include <linux/module.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");

static int my_probe(struct platform_device *pdev) {
	pr_info("probe 호출\n");
	return 0;
}

static const struct of_device_id my_of_match[] = {
	{ .compatible = "test,myprobe" },
	{},
};
MODULE_DEVICE_TABLE(of, my_of_match);

static struct platform_driver my_driver = {
	.probe = my_probe,
	.driver = {
		.name = "myprobe_driver",
		.of_match_table = my_of_match,
	},
};

module_platform_driver(my_driver);
