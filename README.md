# BFD
Utilizing functionality of the Binary File Descriptor Library in Advanced Software Course.


<h4>objcopy.c:</h4>
This utitilizes the bfd_get_section_contents() function call to ready memory from specified BFD section. Helps understand the role of the linker in compiling.


<h4>objsects.c:</h4>
Displays all the information seen on the objdump command. Checks all of the sections of the BFD that calls the function and then prints all the information given from objdump. Gets the name, size, vma, offset, and align values.


<h4>objsyms.c:</h4>
Displays all the information seen on the nm linux command. Checks all of the symbols of the BFD that calls the function and calculates their address to display which matches the address given by nm command.


<h4> makefile</h4>
 Compiles all functions. Creates libobdata.a and libobjdata.so so we can both statically or dynamically link our object files.


<h4>gettxt.c:</h4>
Calls function implemented on objcopy.c by compiling with static library.


<h4>getsects.c:</h4>
Calls function implemented on objsects.c by compiling with static library.


<h4>getsyms.c:</h4>
Calls function implemented on objsyms.c by compiling with static library.


<h4>getsyms_dl.c:</h4>
Calls function implemented on objsyms.c by compiling with dynamic library. Tests timing differences between RTLD_NOW and RTLD_LAZY flags


<h4>getsections_dl.c:</h4>
Calls function implemented on objsects.c by compiling with dynamic library. Tests timing differences between RTLD_NOW and RTLD_LAZY flags
