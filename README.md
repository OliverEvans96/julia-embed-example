# Embedding Julia without `RTLD_GLOBAL`?

This example works fine when the host uses `RTLD_GLOBAL` in `dlopen`:
```
$ make
gcc -shared -o plugin.so -std=gnu99 -I'/home/oliver/local/src/julia-1.4.0/include/julia' -fPIC -L'/home/oliver/local/src/julia-1.4.0/lib' -Wl,--export-dynamic -Wl,-rpath,'/home/oliver/local/src/julia-1.4.0/lib' -Wl,-rpath,'/home/oliver/local/src/julia-1.4.0/lib/julia' -ljulia -fPIC plugin.c
gcc -std=c99 -Wall -ldl host.c -o host 

$ ./host
Host - dlopen
Host - dlsym
Host - call plugin_func
Plugin - Getting julia function
Plugin - Boxing input
Plugin - Calling julia function.
Plugin - Unboxing output
Plugin - Returning result
Host - Plugin returned 3.00
Host - dlclose
Host - finished
```

But without `RTLD_GLOBAL`, it fails because it can't access the necessary libraries.
```
$ sed -i 's/RTLD_NOW | RTLD_GLOBAL/RTLD_NOW/' host.c

$ make
gcc -std=c99 -Wall -ldl host.c -o host 

$ ./host
Host - dlopen
Host - dlsym
Host - call plugin_func
fatal: error thrown and no exception handler available.
ErrorException("could not load symbol "jl_n_threads":
./host: undefined symbol: jl_n_threads")
jl_errorf at /buildworker/worker/package_linux64/build/src/rtutils.c:77
jl_dlsym at /buildworker/worker/package_linux64/build/src/dlload.c:269
jl_load_and_lookup at /buildworker/worker/package_linux64/build/src/runtime_ccall.cpp:63
nthreads at ./threadingconstructs.jl:19 [inlined]
__preinit_threads__ at ./task.jl:518
jfptr___preinit_threads___1959.clone_1 at /home/oliver/local/src/julia-1.4.0/lib/julia/sys.so (unknown line)
_jl_invoke at /buildworker/worker/package_linux64/build/src/gf.c:2144 [inlined]
jl_apply_generic at /buildworker/worker/package_linux64/build/src/gf.c:2322
jl_apply at /buildworker/worker/package_linux64/build/src/julia.h:1692 [inlined]
_julia_init at /buildworker/worker/package_linux64/build/src/init.c:765
jl_init_with_image__threading at /buildworker/worker/package_linux64/build/src/jlapi.c:74
jl_init__threading at /buildworker/worker/package_linux64/build/src/jlapi.c:102
plugin_func at ./plugin.so (unknown line)
main at ./host (unknown line)
__libc_start_main at /usr/lib/libc.so.6 (unknown line)
_start at ./host (unknown line)

atexit hook threw an error: ErrorException("could not load symbol "jl_array_del_beg":
./host: undefined symbol: jl_array_del_beg")
```
