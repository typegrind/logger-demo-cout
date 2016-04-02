
#include <typegrind/logger/demo_cout.h>

#include <iostream>
#include <bitset>

namespace typegrind
{
  namespace logger
  {
    demo_cout::demo_cout()
    {
      std::cout << "logger started" << std::endl;
    }

    demo_cout::~demo_cout()
    {
      std::cout << "logger terminating" << std::endl;
    }

    void demo_cout::log_alloc(entry_alloc<demo_cout> const& alloc_info)
    {
      std::cout << "allocation at:" << alloc_info.locationStr << " type:" << alloc_info.typeStr << " canonical:" << alloc_info.canonicalTypeStr << " type_size:" << alloc_info.typeSize << " total_size:" << alloc_info.size << " addr:" << alloc_info.ptr << std::endl;
    }

    void demo_cout::log_free(entry_free<demo_cout> const& free_info)
    {
      std::cout << "free at:" << free_info.locationStr << " type:" << free_info.typeStr << " canonical:" << free_info.canonicalTypeStr << " addr:" << free_info.ptr << std::endl;
    }

    void demo_cout::log_method_enter(method_scope<demo_cout> const& method_info)
    {
      std::cout << "method enter at:" << method_info.locationStr << " method:" << method_info.targetName << " custom_name:" << method_info.customName << " flags:" << std::bitset<32>(method_info.flags) << std::endl;
    }

    void demo_cout::log_method_exit(method_scope<demo_cout> const& method_info)
    {
      std::cout << "method exit at:" << method_info.locationStr << " method:" << method_info.targetName << " custom_name:" << method_info.customName << " flags:" << std::bitset<32>(method_info.flags) << std::endl;
    }

    void demo_cout::log_initializer_enter(initializer_scope<demo_cout> const& initializer_info)
    {
      std::cout << "initializer enter at:" << initializer_info.locationStr << " method:" << initializer_info.targetName << " custom_name:" << initializer_info.customName << " flags:" << std::bitset<32>(initializer_info.flags) << std::endl;
    }

    void demo_cout::log_initializer_exit(initializer_scope<demo_cout> const& initializer_info)
    {
      std::cout << "initializer exit at:" << initializer_info.locationStr << " method:" << initializer_info.targetName << " custom_name:" << initializer_info.customName << " flags:" << std::bitset<32>(initializer_info.flags) << std::endl;
    }

    demo_cout& demo_cout::get()
    {
      static demo_cout instance;

      return instance;
    }
  }


  static int demangle_status_code = 0;
  static char* demangle_buffer = (char*)malloc(2000);
}

