#include <stdio.h>
#include <julia.h>

float plugin_func(float x)
{
  jl_function_t *julia_sqrt;
  jl_value_t *julia_input, *julia_output;
  float result;

  jl_init();

  printf("Plugin - Getting julia function\n");
  julia_sqrt = jl_get_function(jl_main_module, "sqrt");

  printf("Plugin - Boxing input\n");
  julia_input = jl_box_float32(x);

  printf("Plugin - Calling julia function.\n");
  julia_output = jl_call1(julia_sqrt, julia_input);

  printf("Plugin - Unboxing output\n");
  result = jl_unbox_float32(julia_output);

  printf("Plugin - Returning result\n");
  return result;
}
