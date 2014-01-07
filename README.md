C++ Library to read FOF Files (cube, strct, masst) generated from DEUS Consortium cosmology simulations.
http://www.deus-consortium.org/

A simple Makefile is provided as well as two programs using the lib:

FOFReader: sample program to read file and display some infos
    Usage : fofReader <file> <format>
        Formats:
            0: FOF Cube/Multicube
            1: FOF Struct
            2: FOF Masst

getBiggestHalo: simple utility to get biggest halos from Masst files    
      Usage: getBiggestHalo full_path [nbTops]
      Example: getBiggestHalo /mySimulation/post/fof/output00025/ 5