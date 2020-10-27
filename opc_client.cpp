// opc_client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "opcstd/opcda.h"


#include <iostream>
#include <cassert>

//#include <xlOPCSvr/opcda.h>

#include <atlbase.h>

#include <string>
#include <vector>
#include <thread>

#include <comutil.h>

//extern const GUID IID_IOPCServer;
const GUID IID_IOPCServer = { 0x39c13a4d,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3} };
const GUID IID_IOPCItemMgt = { 0x39c13a54,0x011e,0x11d0,{0x96,0x75,0x00,0x20,0xaf,0xd8,0xad,0xb3} };

void ReadItem(IUnknown* pGroupIUnknown, OPCHANDLE hServerItem, VARIANT& varValue)
{
  // value of the item:
  OPCITEMSTATE* pValue = NULL;
  //get a pointer to the IOPCSyncIOInterface:
  CComPtr<IOPCSyncIO> pIOPCSyncIO;
  pGroupIUnknown->QueryInterface(__uuidof(pIOPCSyncIO), (void**)&pIOPCSyncIO);

  // read the item value from cache:
  HRESULT* pErrors = NULL; //to store error code(s)
  HRESULT hr = pIOPCSyncIO->Read(OPC_DS_DEVICE, 1, &hServerItem, &pValue, &pErrors);
  _ASSERT(!hr);
  _ASSERT(pValue != NULL);

  varValue = pValue[0].vDataValue;

  //Release memeory allocated by the OPC server:
  CoTaskMemFree(pErrors);
  pErrors = NULL;

  CoTaskMemFree(pValue);
  pValue = NULL;

}


void func() {
  CoInitialize(nullptr);

  CLSID opc_server_id;

  {
    auto hr = CLSIDFromString(L"eXLerate.OPCServer", &opc_server_id);
    assert(hr == S_OK);
  }

  CComPtr<IOPCServer> opc_server;
  {
    auto hr = CoCreateInstance(opc_server_id, nullptr, CLSCTX_SERVER, IID_IOPCServer, reinterpret_cast<void**>(&opc_server));
    assert(hr == S_OK);
  }

  CComPtr<IOPCItemMgt> item_mgt;
  OPCHANDLE group_handle;
  {
    DWORD update_rate = 500;
    auto hr = opc_server->AddGroup(L"GR1", FALSE, update_rate, 0, 0, 0, 0, &group_handle, &update_rate, IID_IOPCItemMgt, reinterpret_cast<IUnknown**>(&item_mgt));
    assert(hr == S_OK);
  }

  OPCHANDLE item_handle;
  {
    OPCITEMRESULT* results = nullptr;
    HRESULT* errors = nullptr;
    std::vector<wchar_t> path;

    //std::vector<wchar_t> item{ 'i', 't', 'e', 'm', 0 };
    std::vector<wchar_t> item{ 't','e','s','t','a','p','p','l','i','c','a','t','i','o','n','.','0', '.', 'm', 'o', 'v', '1', '1', 'o','.','v', 'a', 'l', 'u', 'e', 0 };
    OPCITEMDEF item_array[1] =
    { {
        /*szAccessPath*/        path.data(),
        /*szItemID*/            item.data(),
        /*bActive*/             FALSE,
        /*hClient*/             1,
        /*dwBlobSize*/          0,
        /*pBlob*/               NULL,
        /*vtRequestedDataType*/ VT_R4,
        /*wReserved*/           0
        } };
    auto hr = item_mgt->AddItems(1, item_array, &results, &errors);
    //assert(hr == S_OK);
    item_handle = results->hServer;

    CoTaskMemFree(results->pBlob);
    CoTaskMemFree(results);

    CoTaskMemFree(errors);
  }
  //CoUninitialize();

}

int main()
{
  std::thread thr1([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });

  std::thread thr2([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });

  std::thread thr3([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });
  std::thread thr4([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });
  std::thread thr5([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });

  std::thread thr6([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });

  std::thread thr7([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });
  std::thread thr8([] {
    for (size_t i = 0; i < 100; ++i) {
      func();
    }
    });
  thr1.join();
  std::cout << "after thr1" << std::endl;
  thr2.join();
  std::cout << "after thr2" << std::endl;
  thr3.join();
  std::cout << "after thr3" << std::endl;
  thr4.join();
  std::cout << "after thr4" << std::endl;
  thr5.join();
  std::cout << "after thr5" << std::endl;
  thr6.join();
  std::cout << "after thr6" << std::endl;
  thr7.join();
  std::cout << "after thr7" << std::endl;
  thr8.join();
  std::cout << "after thr8" << std::endl;
  return 0;
}

