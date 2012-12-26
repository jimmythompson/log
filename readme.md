C++ Logger Class
===

A simple C++ logger class made in order to have some sort of debugging when dealing with other projects.

It's not the most sophisticated logging class in the world, and was meant as a learning exercise instead of using a library such as log4cpp. The Log singleton, wrapped by static methods, uses a stringstream to write to a textfile, the file being defined by the Initialise function.

A quick stack trace function has been added for you to also use in your projects should you feel the need. To get it to work you need to write the macro PUSH_LOG_STACK at the top of your function; this then uses RAII to push, and automatically pop, the method on the stack when it falls out of scope.
