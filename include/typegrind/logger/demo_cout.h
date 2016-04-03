
#ifndef TYPEGRIND_LOGGER_NOP_H_
#define TYPEGRIND_LOGGER_NOP_H_

#define TYPEGRIND_LOG_NEW(locationStr, typeStr, canonicalTypeStr, typeSize, newExpression) (typegrind::logger::entry_alloc<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, typeSize, 0, nullptr} * newExpression)
#define TYPEGRIND_LOG_NEW_ARRAY(locationStr, typeStr, canonicalTypeStr, typeSize, size, newExpression) (typegrind::logger::entry_alloc<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, typeSize, static_cast<unsigned int>(size), nullptr} * newExpression)
#define TYPEGRIND_LOG_OP_NEW(locationStr, typeStr, canonicalTypeStr, typeSize, size, newExpression) (typegrind::logger::entry_alloc<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, typeSize, static_cast<unsigned int>(size), nullptr} * newExpression)
#define TYPEGRIND_LOG_OP_NEW_ARRAY(locationStr, typeStr, canonicalTypeStr, typeSize, size, newExpression) (typegrind::logger::entry_alloc<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, typeSize, static_cast<unsigned int>(size), nullptr} * newExpression)

#define TYPEGRIND_LOG_DELETE(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, nullptr} * ( deleteExpression ))
#define TYPEGRIND_LOG_DELETE_ARRAY(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, nullptr} * ( deleteExpression ))
#define TYPEGRIND_LOG_OP_DELETE(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, nullptr} * ( deleteExpression ))
#define TYPEGRIND_LOG_OP_DELETE_ARRAY(locationStr, typeStr, canonicalTypeStr, deleteExpression) (typegrind::logger::entry_free<typegrind::logger::demo_cout>{typeStr, canonicalTypeStr, locationStr, nullptr} * ( deleteExpression ))

#define TYPEGRIND_LOG_FUNCTION_ENTER(locationStr, targetName, customName, flags) typegrind::logger::method_scope<typegrind::logger::demo_cout> typegrind_scope_guard(targetName, locationStr, customName, flags);
#define TYPEGRIND_LOG_FUNCTION_AUTO_ENTER(locationStr, targetName, customName, flags) /* NOP */

#define TYPEGRIND_DEMANGLE(s) abi::__cxa_demangle((s), typegrind::logger::demangle_buffer, NULL, &typegrind::logger::demangle_status_code) 

namespace typegrind
{
  namespace logger
  {
    template<typename T>
    struct entry_alloc
    {
      const char*         typeStr;
      const char*         canonicalTypeStr;
      const char*         locationStr;
      const unsigned int  typeSize;
      const unsigned int  size;
      const void* ptr;
    };

    template<typename T, typename O>
    O* operator*(entry_alloc<T> alloc_info, O* ptr)
    {
      alloc_info.ptr = ptr;
      T::get().log_alloc(alloc_info);
      return ptr;
    }

    template<typename T, typename O>
    const O* operator*(entry_alloc<T> alloc_info, const O* ptr)
    {
      alloc_info.ptr = ptr;
      T::get().log_alloc(alloc_info);
      return ptr;
    }

    // -----------------------------------------------

    template<typename T>
    struct entry_free
    {
      const char*         typeStr;
      const char*         canonicalTypeStr;
      const char*         locationStr;
      const void*         ptr;
    };

    template<typename T, typename O>
    const O* operator*(entry_free<T> info, const O* ptr)
    {
      info.ptr = ptr;
      T::get().log_free(info);
      return ptr;
    }

    // -----------------------------------------------

    template<typename T>
    struct method_scope
    {
      typedef unsigned long flags_type;

      const char*         targetName;
      const char*         locationStr;
      const char*         customName;
      flags_type          flags;

      method_scope(const char* targetName, const char* locationStr, const char* customName, flags_type flags)
      : targetName(targetName)
      , locationStr(locationStr)
      , customName(customName)
      , flags(flags)
      {
        T::get().log_method_enter(*this);
      }

      ~method_scope()
      {
        T::get().log_method_exit(*this);
      }
    };

    // -----------------------------------------------

    template<typename T>
    struct initializer_scope
    {
      typedef unsigned long flags_type;

      const char*         targetName;
      const char*         locationStr;
      const char*         customName;
      flags_type          flags;

      initializer_scope(const char* targetName, const char* locationStr, const char* customName, flags_type flags)
      : targetName(targetName)
      , locationStr(locationStr)
      , customName(customName)
      , flags(flags)
      {
        T::get().log_initializer_enter(*this);
      }

      ~initializer_scope()
      {
        T::get().log_initializer_exit(*this);
      }

      explicit operator bool() const
      {
        return true;
      }
    };

    static int demangle_status_code;
    static char* demangle_buffer;





    class demo_cout
    {
    public:
      demo_cout();
      ~demo_cout();
      
      void log_alloc(entry_alloc<demo_cout> const& alloc_info);
      void log_free(entry_free<demo_cout> const& free_info);

      void log_method_enter(method_scope<demo_cout> const& alloc_info);
      void log_method_exit(method_scope<demo_cout> const& free_info);

      void log_initializer_enter(initializer_scope<demo_cout> const& method_info);
      void log_initializer_exit(initializer_scope<demo_cout> const& initializer_info);

      static demo_cout& get();
    };


  }
}

#endif
