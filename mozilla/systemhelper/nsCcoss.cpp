#include "nsCcoss.h"

#include "stdlib.h"

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsCcoss, nsICcoss)

nsCcoss::nsCcoss()
{
  /* member initializers and constructor code */
}

nsCcoss::~nsCcoss()
{
  /* destructor code */
}

/* void reboot (); */
NS_IMETHODIMP nsCcoss::Reboot()
{
	system("/sbin/reboot_helper");
    return NS_OK;
}

/* void shutdown (); */
NS_IMETHODIMP nsCcoss::Shutdown()
{
	system("/sbin/shutdown_helper");
    return NS_OK;
}
