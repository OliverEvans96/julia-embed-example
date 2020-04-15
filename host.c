#include <stdio.h>
#include <dlfcn.h>

int main() {
  void *plugin_lib;
  float(*plugin_func)(float x);
  float plugin_result;

  printf("Host - dlopen\n");
  plugin_lib = dlopen("./plugin.so", RTLD_NOW);

  printf("Host - dlsym\n");
  plugin_func = dlsym(plugin_lib, "plugin_func");

  printf("Host - call plugin_func\n");
  plugin_result = plugin_func(9.0f);
  printf("Host - Plugin returned %.2f\n", plugin_result);

  printf("Host - dlclose\n");
  dlclose(plugin_lib);

  printf("Host - finished\n");
  return 0;
}
