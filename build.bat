windres hydra.rc -o hydra_res.o 
gcc hydra.c hydra_res.o -o hydra.exe -mwindows
