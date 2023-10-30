#include "wrapper.h"

zend_string *ext_php_rs_zend_string_init(const char *str, size_t len, bool persistent) {
  return zend_string_init(str, len, persistent);
}

void ext_php_rs_zend_string_release(zend_string *zs) {
  zend_string_release(zs);
}

bool ext_php_rs_is_known_valid_utf8(const zend_string *zs) {
  return GC_FLAGS(zs) & IS_STR_VALID_UTF8;
}

void ext_php_rs_set_known_valid_utf8(zend_string *zs) {
  if (!ZSTR_IS_INTERNED(zs)) {
    GC_ADD_FLAGS(zs, IS_STR_VALID_UTF8);
  }
}

const char *ext_php_rs_php_build_id() { return ZEND_MODULE_BUILD_ID; }

void *ext_php_rs_zend_object_alloc(size_t obj_size, zend_class_entry *ce) {
  return zend_object_alloc(obj_size, ce);
}

void ext_php_rs_zend_object_release(zend_object *obj) {
  zend_object_release(obj);
}

zend_executor_globals *ext_php_rs_executor_globals() {
#ifdef ZTS
#ifdef ZEND_ENABLE_STATIC_TSRMLS_CACHE
  return TSRMG_FAST_BULK_STATIC(executor_globals_offset, zend_executor_globals);
#else
  return TSRMG_FAST_BULK(executor_globals_offset, zend_executor_globals *);
#endif
#else
  return &executor_globals;
#endif
}

bool ext_php_rs_zend_try_catch(void* (*callback)(void *), void *ctx, void **result) {
  zend_try {
    *result = callback(ctx);
  } zend_catch {
    return true;
  } zend_end_try();

  return false;
}

bool ext_php_rs_zend_first_try_catch(void* (*callback)(void *), void *ctx, void **result) {
  zend_first_try {
    *result = callback(ctx);
  } zend_catch {
    return true;
  } zend_end_try();

  return false;
}

void ext_php_rs_zend_bailout() {
  zend_bailout();
}
