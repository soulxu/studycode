#ifndef _NSCCOSS_H_
#define _NSCCOSS_H_

#include "nsIClassInfoImpl.h"
#include "nsICcoss.h"

//复制自，自动通过idl文件自动生成的头文件中，同样是uuid的十六进制保存方式
#define NS_ICCOSS_CID \
  {0xa938f306, 0xd249, 0x4527, \
    { 0xac, 0x4b, 0x2c, 0x05, 0xea, 0xfb, 0xf6, 0x25 }}

//访问接口的ID标识，如在js脚本中，通过这个id来查找和访问该接口
#define NS_CCOSS_CONTRACTID "@ccoss.com/desktop;1"

//简单描述
#define NS_CCOSS_CLASSNAME "Sample ccoss Interface Layer"


//复制自自动生成的头文件
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

#endif
