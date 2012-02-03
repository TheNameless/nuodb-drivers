
//
// Copyright NUODB, Inc. All rigts reserved
//
// Copyright (C) 2011 Rus V. Brushkoff <rus@sfinxsoft.com>
//

#ifndef PHP_NUODB_H
#define PHP_NUODB_H

//TSRMLS_FETCH(); 

extern zend_module_entry nuodb_module_entry;
#define phpext_nuodb_ptr &nuodb_module_entry

#ifdef PHP_WIN32
#	define PHP_NUODB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_NUODB_API __attribute__ ((visibility("default")))
#else
#	define PHP_NUODB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "Connection.h"
#include "SQLException.h"
#include "Properties.h"

PHP_MINIT_FUNCTION(nuodb);
PHP_MSHUTDOWN_FUNCTION(nuodb);
PHP_RINIT_FUNCTION(nuodb);
PHP_RSHUTDOWN_FUNCTION(nuodb);
PHP_MINFO_FUNCTION(nuodb);

PHP_FUNCTION(nuodb_error);
PHP_FUNCTION(nuodb_connect);
PHP_FUNCTION(nuodb_autocommit);
PHP_FUNCTION(nuodb_disconnect);
PHP_FUNCTION(nuodb_query);
PHP_FUNCTION(nuodb_free_result);
PHP_FUNCTION(nuodb_fetch_array);

ZEND_BEGIN_MODULE_GLOBALS(nuodb)
//            long num_links;
//            long num_persistent;
//            long max_links,max_persistent;
//            long connect_timeout; 
//            long results_allocated;
            long debug, trace;
ZEND_END_MODULE_GLOBALS(nuodb)

// added by T.Gates 1/8/2012
//ZEND_EXTERN_MODULE_GLOBALS(nuodb)

/* In every utility function you add that needs to use variables 
   in php_nuodb_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as NUODB_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define NUODB_G(v) TSRMG(nuodb_globals_id, zend_nuodb_globals *, v)
#else
#define NUODB_G(v) (nuodb_globals.v)
#endif


#ifdef WIN32
/* hash */

  using std::size_t;

  template<class _Key>
    struct hash { };

  inline size_t
  __stl_hash_string(const char* __s)
  {
    unsigned long __h = 0;
    for ( ; *__s; ++__s)
      __h = 5 * __h + *__s;
    return size_t(__h);
  }

  template<>
    struct hash<char*>
    {
      size_t
      operator()(const char* __s) const
      { return __stl_hash_string(__s); }
    };

  template<>
    struct hash<const char*>
    {
      size_t
      operator()(const char* __s) const
      { return __stl_hash_string(__s); }
    };

  template<>
    struct hash<char>
    { 
      size_t
      operator()(char __x) const
      { return __x; }
    };

  template<>
    struct hash<unsigned char>
    { 
      size_t
      operator()(unsigned char __x) const
      { return __x; }
    };

  template<>
    struct hash<signed char>
    {
      size_t
      operator()(unsigned char __x) const
      { return __x; }
    };

  template<>
    struct hash<short>
    {
      size_t
      operator()(short __x) const
      { return __x; }
    };

  template<>
    struct hash<unsigned short>
    {
      size_t
      operator()(unsigned short __x) const
      { return __x; }
    };

  template<>
    struct hash<int>
    { 
      size_t 
      operator()(int __x) const 
      { return __x; }
    };

  template<>
    struct hash<unsigned int>
    { 
      size_t
      operator()(unsigned int __x) const
      { return __x; }
    };

  template<>
    struct hash<long>
    {
      size_t
      operator()(long __x) const
      { return __x; }
    };

  template<>
    struct hash<unsigned long>
    {
      size_t
      operator()(unsigned long __x) const
      { return __x; }
    };

#endif


#endif	/* PHP_NUODB_H */