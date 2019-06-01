#include <stdio.h>
#include "../riscv_iface.h"

int main() {
  int a, b;
  int mul, mul8_303, mul8_469, mul8_479, mul8_423, mul8_279;

  for (a = 0; a < 255; a++) {
    for (b = -3; b <= 3; b++) {
      mul = a*b;
      vac_activate(VAC_APPROX_MUL8_303);
      mul8_303 = a * b;
      vac_deactivate(VAC_APPROX_MUL8_303);
      vac_activate(VAC_APPROX_MUL8_469);
      mul8_469 = a * b;
      vac_deactivate(VAC_APPROX_MUL8_469);
      vac_activate(VAC_APPROX_MUL8_479);
      mul8_479 = a * b;
      vac_deactivate(VAC_APPROX_MUL8_479);
      vac_activate(VAC_APPROX_MUL8_423);
      mul8_423 = a * b;
      vac_deactivate(VAC_APPROX_MUL8_423);
      vac_activate(VAC_APPROX_MUL8_279);
      mul8_279 = a * b;
      vac_deactivate(VAC_APPROX_MUL8_279);
      printf("%d * %d = %d\n\t303: %d\n\t469: %d\n\t479: %d\n\t423: %d\n\t279: %d\n\n", a, b, mul, mul8_303, mul8_469, mul8_479, mul8_423, mul8_279);
    }
  }

  return 0;
}

