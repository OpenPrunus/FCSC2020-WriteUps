/* Automically generated by wasm2c */
#include <math.h>
#include <string.h>

#include "index.h"
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define LIKELY(x) __builtin_expect(!!(x), 1)

#define TRAP(x) (wasm_rt_trap(WASM_RT_TRAP_##x), 0)

#define FUNC_PROLOGUE                                            \
  if (++wasm_rt_call_stack_depth > WASM_RT_MAX_CALL_STACK_DEPTH) \
    TRAP(EXHAUSTION)

#define FUNC_EPILOGUE --wasm_rt_call_stack_depth

#define UNREACHABLE TRAP(UNREACHABLE)

#define CALL_INDIRECT(table, t, ft, x, ...)          \
  (LIKELY((x) < table.size && table.data[x].func &&  \
          table.data[x].func_type == func_types[ft]) \
       ? ((t)table.data[x].func)(__VA_ARGS__)        \
       : TRAP(CALL_INDIRECT))

#define MEMCHECK(mem, a, t)  \
  if (UNLIKELY((a) + sizeof(t) > mem->size)) TRAP(OOB)

#define DEFINE_LOAD(name, t1, t2, t3)              \
  static inline t3 name(wasm_rt_memory_t* mem, u64 addr) {   \
    MEMCHECK(mem, addr, t1);                       \
    t1 result;                                     \
    memcpy(&result, &mem->data[addr], sizeof(t1)); \
    return (t3)(t2)result;                         \
  }

#define DEFINE_STORE(name, t1, t2)                           \
  static inline void name(wasm_rt_memory_t* mem, u64 addr, t2 value) { \
    MEMCHECK(mem, addr, t1);                                 \
    t1 wrapped = (t1)value;                                  \
    memcpy(&mem->data[addr], &wrapped, sizeof(t1));          \
  }

DEFINE_LOAD(i32_load, u32, u32, u32);
DEFINE_LOAD(i64_load, u64, u64, u64);
DEFINE_LOAD(f32_load, f32, f32, f32);
DEFINE_LOAD(f64_load, f64, f64, f64);
DEFINE_LOAD(i32_load8_s, s8, s32, u32);
DEFINE_LOAD(i64_load8_s, s8, s64, u64);
DEFINE_LOAD(i32_load8_u, u8, u32, u32);
DEFINE_LOAD(i64_load8_u, u8, u64, u64);
DEFINE_LOAD(i32_load16_s, s16, s32, u32);
DEFINE_LOAD(i64_load16_s, s16, s64, u64);
DEFINE_LOAD(i32_load16_u, u16, u32, u32);
DEFINE_LOAD(i64_load16_u, u16, u64, u64);
DEFINE_LOAD(i64_load32_s, s32, s64, u64);
DEFINE_LOAD(i64_load32_u, u32, u64, u64);
DEFINE_STORE(i32_store, u32, u32);
DEFINE_STORE(i64_store, u64, u64);
DEFINE_STORE(f32_store, f32, f32);
DEFINE_STORE(f64_store, f64, f64);
DEFINE_STORE(i32_store8, u8, u32);
DEFINE_STORE(i32_store16, u16, u32);
DEFINE_STORE(i64_store8, u8, u64);
DEFINE_STORE(i64_store16, u16, u64);
DEFINE_STORE(i64_store32, u32, u64);

#define I32_CLZ(x) ((x) ? __builtin_clz(x) : 32)
#define I64_CLZ(x) ((x) ? __builtin_clzll(x) : 64)
#define I32_CTZ(x) ((x) ? __builtin_ctz(x) : 32)
#define I64_CTZ(x) ((x) ? __builtin_ctzll(x) : 64)
#define I32_POPCNT(x) (__builtin_popcount(x))
#define I64_POPCNT(x) (__builtin_popcountll(x))

#define DIV_S(ut, min, x, y)                                 \
   ((UNLIKELY((y) == 0)) ?                TRAP(DIV_BY_ZERO)  \
  : (UNLIKELY((x) == min && (y) == -1)) ? TRAP(INT_OVERFLOW) \
  : (ut)((x) / (y)))

#define REM_S(ut, min, x, y)                                \
   ((UNLIKELY((y) == 0)) ?                TRAP(DIV_BY_ZERO) \
  : (UNLIKELY((x) == min && (y) == -1)) ? 0                 \
  : (ut)((x) % (y)))

#define I32_DIV_S(x, y) DIV_S(u32, INT32_MIN, (s32)x, (s32)y)
#define I64_DIV_S(x, y) DIV_S(u64, INT64_MIN, (s64)x, (s64)y)
#define I32_REM_S(x, y) REM_S(u32, INT32_MIN, (s32)x, (s32)y)
#define I64_REM_S(x, y) REM_S(u64, INT64_MIN, (s64)x, (s64)y)

#define DIVREM_U(op, x, y) \
  ((UNLIKELY((y) == 0)) ? TRAP(DIV_BY_ZERO) : ((x) op (y)))

#define DIV_U(x, y) DIVREM_U(/, x, y)
#define REM_U(x, y) DIVREM_U(%, x, y)

#define ROTL(x, y, mask) \
  (((x) << ((y) & (mask))) | ((x) >> (((mask) - (y) + 1) & (mask))))
#define ROTR(x, y, mask) \
  (((x) >> ((y) & (mask))) | ((x) << (((mask) - (y) + 1) & (mask))))

#define I32_ROTL(x, y) ROTL(x, y, 31)
#define I64_ROTL(x, y) ROTL(x, y, 63)
#define I32_ROTR(x, y) ROTR(x, y, 31)
#define I64_ROTR(x, y) ROTR(x, y, 63)

#define FMIN(x, y)                                          \
   ((UNLIKELY((x) != (x))) ? NAN                            \
  : (UNLIKELY((y) != (y))) ? NAN                            \
  : (UNLIKELY((x) == 0 && (y) == 0)) ? (signbit(x) ? x : y) \
  : (x < y) ? x : y)

#define FMAX(x, y)                                          \
   ((UNLIKELY((x) != (x))) ? NAN                            \
  : (UNLIKELY((y) != (y))) ? NAN                            \
  : (UNLIKELY((x) == 0 && (y) == 0)) ? (signbit(x) ? y : x) \
  : (x > y) ? x : y)

#define TRUNC_S(ut, st, ft, min, max, maxop, x)                             \
   ((UNLIKELY((x) != (x))) ? TRAP(INVALID_CONVERSION)                       \
  : (UNLIKELY((x) < (ft)(min) || (x) maxop (ft)(max))) ? TRAP(INT_OVERFLOW) \
  : (ut)(st)(x))

#define I32_TRUNC_S_F32(x) TRUNC_S(u32, s32, f32, INT32_MIN, INT32_MAX, >=, x)
#define I64_TRUNC_S_F32(x) TRUNC_S(u64, s64, f32, INT64_MIN, INT64_MAX, >=, x)
#define I32_TRUNC_S_F64(x) TRUNC_S(u32, s32, f64, INT32_MIN, INT32_MAX, >,  x)
#define I64_TRUNC_S_F64(x) TRUNC_S(u64, s64, f64, INT64_MIN, INT64_MAX, >=, x)

#define TRUNC_U(ut, ft, max, maxop, x)                                    \
   ((UNLIKELY((x) != (x))) ? TRAP(INVALID_CONVERSION)                     \
  : (UNLIKELY((x) <= (ft)-1 || (x) maxop (ft)(max))) ? TRAP(INT_OVERFLOW) \
  : (ut)(x))

#define I32_TRUNC_U_F32(x) TRUNC_U(u32, f32, UINT32_MAX, >=, x)
#define I64_TRUNC_U_F32(x) TRUNC_U(u64, f32, UINT64_MAX, >=, x)
#define I32_TRUNC_U_F64(x) TRUNC_U(u32, f64, UINT32_MAX, >,  x)
#define I64_TRUNC_U_F64(x) TRUNC_U(u64, f64, UINT64_MAX, >=, x)

#define DEFINE_REINTERPRET(name, t1, t2)  \
  static inline t2 name(t1 x) {           \
    t2 result;                            \
    memcpy(&result, &x, sizeof(result));  \
    return result;                        \
  }

DEFINE_REINTERPRET(f32_reinterpret_i32, u32, f32)
DEFINE_REINTERPRET(i32_reinterpret_f32, f32, u32)
DEFINE_REINTERPRET(f64_reinterpret_i64, u64, f64)
DEFINE_REINTERPRET(i64_reinterpret_f64, f64, u64)


static u32 func_types[4];

static void init_func_types(void) {
  func_types[0] = wasm_rt_register_func_type(1, 1, WASM_RT_I32, WASM_RT_I32);
  func_types[1] = wasm_rt_register_func_type(0, 0);
  func_types[2] = wasm_rt_register_func_type(1, 0, WASM_RT_I32);
  func_types[3] = wasm_rt_register_func_type(0, 1, WASM_RT_I32);
}

static void e(u32);
static u32 d(u32);
static u32 c(void);
static u32 f3(u32);
static u32 b(u32);
static void a(void);

static u32 g0;

static void init_globals(void) {
  g0 = 5244480u;
}

static void e(u32 p0) {
  FUNC_PROLOGUE;
  u32 i0;
  i0 = p0;
  g0 = i0;
  FUNC_EPILOGUE;
}

static u32 d(u32 p0) {
  FUNC_PROLOGUE;
  u32 i0, i1;
  i0 = g0;
  i1 = p0;
  i0 -= i1;
  i1 = 4294967280u;
  i0 &= i1;
  p0 = i0;
  g0 = i0;
  i0 = p0;
  FUNC_EPILOGUE;
  return i0;
}

static u32 c(void) {
  FUNC_PROLOGUE;
  u32 i0;
  i0 = g0;
  FUNC_EPILOGUE;
  return i0;
}

static u32 f3(u32 p0) {
  u32 l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0;
  FUNC_PROLOGUE;
  u32 i0, i1;
  i0 = 70u;
  l3 = i0;
  i0 = 1024u;
  l1 = i0;
  i0 = p0;
  i0 = i32_load8_u(Z_aZ_memory, (u64)(i0));
  l2 = i0;
  i0 = !(i0);
  if (i0) {goto B0;}
  L1: 
    i0 = l2;
    i1 = l1;
    i1 = i32_load8_u(Z_aZ_memory, (u64)(i1));
    l4 = i1;
    i0 = i0 != i1;
    if (i0) {goto B2;}
    i0 = l3;
    i1 = 4294967295u;
    i0 += i1;
    l3 = i0;
    i0 = !(i0);
    if (i0) {goto B2;}
    i0 = l4;
    i0 = !(i0);
    if (i0) {goto B2;}
    i0 = l1;
    i1 = 1u;
    i0 += i1;
    l1 = i0;
    i0 = p0;
    i0 = i32_load8_u(Z_aZ_memory, (u64)(i0) + 1u);
    l2 = i0;
    i0 = p0;
    i1 = 1u;
    i0 += i1;
    p0 = i0;
    i0 = l2;
    if (i0) {goto L1;}
    goto B0;
    B2:;
  i0 = l2;
  l5 = i0;
  B0:;
  i0 = l5;
  i1 = 255u;
  i0 &= i1;
  i1 = l1;
  i1 = i32_load8_u(Z_aZ_memory, (u64)(i1));
  i0 -= i1;
  FUNC_EPILOGUE;
  return i0;
}

static u32 b(u32 p0) {
  u32 l1 = 0, l2 = 0;
  FUNC_PROLOGUE;
  u32 i0, i1, i2;
  i0 = p0;
  i0 = i32_load8_u(Z_aZ_memory, (u64)(i0));
  l2 = i0;
  if (i0) {
    i0 = p0;
    l1 = i0;
    L1: 
      i0 = l1;
      i1 = l2;
      i2 = 3u;
      i1 ^= i2;
      i32_store8(Z_aZ_memory, (u64)(i0), i1);
      i0 = l1;
      i0 = i32_load8_u(Z_aZ_memory, (u64)(i0) + 1u);
      l2 = i0;
      i0 = l1;
      i1 = 1u;
      i0 += i1;
      l1 = i0;
      i0 = l2;
      if (i0) {goto L1;}
  }
  i0 = p0;
  i0 = f3(i0);
  i0 = !(i0);
  FUNC_EPILOGUE;
  return i0;
}

static void a(void) {
  FUNC_PROLOGUE;
  FUNC_EPILOGUE;
}

static const u8 data_segment_data_0[] = {
  0x45, 0x40, 0x50, 0x40, 0x78, 0x34, 0x66, 0x31, 0x67, 0x37, 0x66, 0x36, 
  0x61, 0x62, 0x3a, 0x34, 0x32, 0x60, 0x31, 0x67, 0x3a, 0x66, 0x3a, 0x37, 
  0x37, 0x36, 0x33, 0x31, 0x33, 0x33, 0x3b, 0x65, 0x30, 0x65, 0x3b, 0x30, 
  0x33, 0x60, 0x36, 0x36, 0x36, 0x31, 0x60, 0x62, 0x65, 0x65, 0x30, 0x3a, 
  0x33, 0x33, 0x66, 0x67, 0x37, 0x33, 0x32, 0x3b, 0x62, 0x36, 0x66, 0x65, 
  0x61, 0x34, 0x34, 0x62, 0x65, 0x33, 0x34, 0x67, 0x30, 0x7e, 
};

static void init_memory(void) {
  memcpy(&((*Z_aZ_memory).data[1024u]), data_segment_data_0, 70);
}

static void init_table(void) {
  uint32_t offset;
}

/* export: 'a' */
void (*WASM_RT_ADD_PREFIX(Z_aZ_vv))(void);
/* export: 'b' */
u32 (*WASM_RT_ADD_PREFIX(Z_bZ_ii))(u32);
/* export: 'c' */
u32 (*WASM_RT_ADD_PREFIX(Z_cZ_iv))(void);
/* export: 'd' */
u32 (*WASM_RT_ADD_PREFIX(Z_dZ_ii))(u32);
/* export: 'e' */
void (*WASM_RT_ADD_PREFIX(Z_eZ_vi))(u32);

static void init_exports(void) {
  /* export: 'a' */
  WASM_RT_ADD_PREFIX(Z_aZ_vv) = (&a);
  /* export: 'b' */
  WASM_RT_ADD_PREFIX(Z_bZ_ii) = (&b);
  /* export: 'c' */
  WASM_RT_ADD_PREFIX(Z_cZ_iv) = (&c);
  /* export: 'd' */
  WASM_RT_ADD_PREFIX(Z_dZ_ii) = (&d);
  /* export: 'e' */
  WASM_RT_ADD_PREFIX(Z_eZ_vi) = (&e);
}

void WASM_RT_ADD_PREFIX(init)(void) {
  init_func_types();
  init_globals();
  init_memory();
  init_table();
  init_exports();
}
