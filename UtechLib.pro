TEMPLATE    = subdirs
SUBDIRS     = src/src.pro

system('cd src & qmake')
message("UtechLib configured successfuly. Now you can compile library.")
