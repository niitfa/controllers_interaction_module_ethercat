# src/Makefile

SRC = $(wildcard *.$(SRC_EXT))
OBJ = $(patsubst %.$(SRC_EXT), $(PREFIX_OBJ)%.o, $(SRC))
SUBDIRS = $(shell ls -d */)

all: obj recursive 

recursive:
	for subdir in $(SUBDIRS); do \
	cd $(PREFIX_SRC)$$subdir;\
	${MAKE} all;\
	cd ../;\
	done

obj: $(OBJ)

$(PREFIX_OBJ)%.o : %.$(SRC_EXT)
	$(CC) -c $< -o $@ $(CCFLAGS)


