#include "stock_firmware_common.h"
#include "stm32h7xx_hal.h"

int32_t (* const stock_flash_init)(void) = 0x0800a40c | THUMB;

int32_t flash_init() {
  return stock_flash_init();
}

int32_t (* const stock_flash_cmd)(int32_t arg01, int32_t arg02, void* arg03, int32_t arg04, int32_t arg05, int32_t arg06, int32_t* arg07, int32_t* arg08,
                                  int32_t arg09, int32_t arg10, int32_t arg11, int32_t arg12, int32_t arg13, int32_t arg14, int32_t arg15, int32_t arg16, int32_t arg17) = 0x08007b32 | THUMB;

int32_t flash_cmd(int32_t arg01, int32_t arg02, void* arg03, int32_t arg04, int32_t arg05, int32_t arg06, int32_t* arg07, int32_t* arg08,
                  int32_t arg09, int32_t arg10, int32_t arg11, int32_t arg12, int32_t arg13, int32_t arg14, int32_t arg15, int32_t arg16, int32_t arg17) {
  return stock_flash_cmd(arg01, arg02, arg03, arg04, arg05, arg06, arg07, arg08, arg09, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17);
}

int32_t (* const stock_flash_read_reg)(int32_t arg1, char* arg2, int32_t arg3) = 0x08007766 | THUMB;

int32_t flash_read_reg(int32_t arg1, char* arg2, int32_t arg3) {
  return stock_flash_read_reg(arg1, arg2, arg3);
}

int32_t (* const stock_flash_write_reg)(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7) = 0x08007766 | THUMB;

int32_t flash_write_reg(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7) {
  return stock_flash_write_reg(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

int32_t (* const stock_flash_reset)(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0x08004f3c | THUMB;

int32_t flash_reset(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) {
  return stock_flash_reset(arg1, arg2, arg3, arg4);
}
