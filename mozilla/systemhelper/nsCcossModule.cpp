#include "nsIGenericFactory.h"
#include "nsCcoss.h"
 
//每个组件都必须存在这样一个实现文件，用来注册组件

NS_GENERIC_FACTORY_CONSTRUCTOR(nsCcoss)
 
//NS_DECL_CLASSINFO(nsCcoss)


//组件信息 ,还可以定义组件构造和析构使用的函数
static const nsModuleComponentInfo components[] = {
  {  NS_CCOSS_CLASSNAME, 
     NS_ICCOSS_CID, 
     NS_CCOSS_CONTRACTID,
     nsCcossConstructor
  }
};

//注册组件
NS_IMPL_NSGETMODULE(nsCcossModule, components)
