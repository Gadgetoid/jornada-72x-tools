jornada_add_library(greet greet.c EXPORTS Add Greeting)
jornada_add_executable(greeter greeter.c)
add_dependencies(greeter greet)
