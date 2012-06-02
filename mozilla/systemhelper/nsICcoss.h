/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsICcoss.idl
 */

#ifndef __gen_nsICcoss_h__
#define __gen_nsICcoss_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsICcoss */
#define NS_ICCOSS_IID_STR "a938f306-d249-4527-ac4b-2c05eafbf625"

#define NS_ICCOSS_IID \
  {0xa938f306, 0xd249, 0x4527, \
    { 0xac, 0x4b, 0x2c, 0x05, 0xea, 0xfb, 0xf6, 0x25 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsICcoss : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICCOSS_IID)

  /* void reboot (); */
  NS_SCRIPTABLE NS_IMETHOD Reboot(void) = 0;

  /* void shutdown (); */
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsICcoss, NS_ICCOSS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICCOSS \
  NS_SCRIPTABLE NS_IMETHOD Reboot(void); \
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICCOSS(_to) \
  NS_SCRIPTABLE NS_IMETHOD Reboot(void) { return _to Reboot(); } \
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void) { return _to Shutdown(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICCOSS(_to) \
  NS_SCRIPTABLE NS_IMETHOD Reboot(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Reboot(); } \
  NS_SCRIPTABLE NS_IMETHOD Shutdown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Shutdown(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsCcoss : public nsICcoss
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICCOSS

  nsCcoss();

private:
  ~nsCcoss();

protected:
  /* additional members */
};

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
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void shutdown (); */
NS_IMETHODIMP nsCcoss::Shutdown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsICcoss_h__ */
