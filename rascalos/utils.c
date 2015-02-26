#include <rascalos.h>

#include <linux/module.h>

#define RASCALOS_MODULE_NAME	"rascalos"

static struct mod *rascal_module = NULL;

/* Attempts to take a reference on RascalOS, loading the module when necessary.
   It is the caller's responsibility to ensure the reference is given up at a
   suitable opportunity.
   
   Code mostly borrowed from DIOS. */
static struct module *check_module_loaded(void)
{
	struct module *mod = NULL;
	
	if (mutex_lock_interruptible(&module_mutex) != 0)
		return NULL;
	mod = find_module(RASCALOS_MODULE_NAME);

	printk((mod == NULL)
		? "RascalOS module is not loaded.\n"
		: "RascalOS module is loaded.\n"
	);

	return mod;
}

int get_rascalos(void)
{
	// Is the module loaded yet?
	if (!rascal_module)
		rascal_module = check_module_loaded();
	if (!rascal_module)
		if (request_module(RASCALOS_MODULE_NAME))
			goto fail;
	
	// Should be ready to go
/*	if (!try_module_get(rascal_module))
		goto fail;*/
	return 0;
fail:
	printk("We couldn't load the RascalOS module. Fail.\n");
	return -ENOSYS;
}
