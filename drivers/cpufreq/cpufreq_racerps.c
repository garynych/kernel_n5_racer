/*
 *  linux/drivers/cpufreq/cpufreq_racerps.c
 *
 *  Copyright (C) 2002 - 2003 Dominik Brodowski <linux@brodo.de>
 *  Copyright (C) 2014 - 2015 Ravikumar Achanta <ravikumar.achanta@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cpufreq.h>
#include <linux/init.h>

static int cpufreq_governor_racerps(struct cpufreq_policy *policy,
					unsigned int event)
{
	switch (event) {
	case CPUFREQ_GOV_START:
	case CPUFREQ_GOV_LIMITS:
		pr_debug("setting to %u kHz because of event %u\n",
							960000, event);
		__cpufreq_driver_target(policy, 960000,
						CPUFREQ_RELATION_L);
		break;
	default:
		break;
	}
	return 0;
}

#ifndef CONFIG_CPU_FREQ_DEFAULT_GOV_RACER_PS
static
#endif
struct cpufreq_governor cpufreq_gov_racerps = {
	.name		= "racerps",
	.governor	= cpufreq_governor_racerps,
	.owner		= THIS_MODULE,
};

static int __init cpufreq_gov_racerps_init(void)
{
	return cpufreq_register_governor(&cpufreq_gov_racerps);
}


static void __exit cpufreq_gov_racerps_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_racerps);
}


MODULE_AUTHOR("Ravikumar Achanta <ravikumar.achanta@gmail.com> based on work by Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq policy governor 'racerps'");
MODULE_LICENSE("GPL");

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_RACER_PS
fs_initcall(cpufreq_gov_racerps_init);
#else
module_init(cpufreq_gov_racerps_init);
#endif
module_exit(cpufreq_gov_racerps_exit);
