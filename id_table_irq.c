
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/etherdevice.h>



static DEFINE_PCI_DEVICE_TABLE(my_table) = {
	{PCI_DEVICE(0x8086, 0x100e)},
	{}
};

MODULE_DEVICE_TABLE(pci, my_table);

static int my_probe (struct pci_dev *pdev, const struct pci_device_id *id)
{
	// allocate etherdev	alloc_etherdev
	struct net_device *ndev = alloc_etherdev(100);
	// Fill required structure members
	// register with net_device subsystem
	printk("probe called irq :%d ", pdev->irq);
	printk("mmio :%x\n", (unsigned int )pci_resource_start(pdev, 0));
	return 0;
}


static struct pci_driver my_driver = {
	.name = KBUILD_MODNAME,
	.probe = my_probe,
	.id_table = my_table,
};

int irq_init(void)
{
	int ret;
	printk("irq_init.\n");
	ret = pci_register_driver(&my_driver);
	printk("ret :%d\n", ret);

	return 0;
}

void irq_exit(void)
{
	pci_unregister_driver(&my_driver);
	printk("irq_exit.-----------------\n");
}

module_init(irq_init);
module_exit(irq_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IRQSHARE Test");

