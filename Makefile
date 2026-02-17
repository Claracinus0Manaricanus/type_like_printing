INC = -I./include
o_dir = ./build

all: $(o_dir)/cm_tlp.o

test: $(o_dir)/test

$(o_dir):
	mkdir build

$(o_dir)/cm_tlp.o: $(o_dir)
	cc -c $(INC) -o $(o_dir)/cm_tlp.o src/cm_tlp.c

$(o_dir)/test: $(o_dir) $(o_dir)/cm_tlp.o
	cc $(INC) -o $(o_dir)/test ./tests/test.c $(o_dir)/cm_tlp.o
