INC = -I./include
o_dir = ./build

all: $(o_dir) $(o_dir)/libcm_tlp.so $(o_dir)/libcm_tlp.a

test: $(o_dir) $(o_dir)/test

$(o_dir):
	mkdir build

$(o_dir)/libcm_tlp.so:
	cc --shared $(INC) -o $(o_dir)/libcm_tlp.so src/cm_tlp.c

$(o_dir)/libcm_tlp.o:
	cc -c $(INC) -o $(o_dir)/libcm_tlp.o src/cm_tlp.c

$(o_dir)/libcm_tlp.a: $(o_dir)/libcm_tlp.o
	ar rcs $(o_dir)/libcm_tlp.a $(o_dir)/libcm_tlp.o

$(o_dir)/test: $(o_dir)/libcm_tlp.o
	cc $(INC) -o $(o_dir)/test ./tests/test.c $(o_dir)/libcm_tlp.o
