NAME = fractol

HDRDIR = header
SRCDIR = src
CUDASRC = cudasrc
CUDAHDR = cudaheader

CSRC =	$(CUDASRC)/test.cu

COBJ =	test.o

SOURCE = 	$(SRCDIR)/main.c

OBJ = 	main.o

FLAGS = -Wall -Werror -Wextra -iquote header -framework OpenGL -framework AppKit #-I/usr/X11/include

LINFTHDR = libft/includes
LIBFTDIR = libft/
LIBFT =  $(LIBFTDIR)libft.a

#MLXDIR = minilibx_macos/
#MLXLIB = $(MLXDIR)libmlx.a
LIB = -L/usr/X11/lib -lmlx -lXext -lX11 -I /opt/X11/include/

CUDA=/Developer/NVIDIA/CUDA-5.5
NVCC=/Developer/NVIDIA/CUDA-5.5/bin/nvcc
NVCC_C = -ccbin /usr/bin/clang -m64
NVCC_FRAMEWORK = -Xlinker -framework,OpenGL -Xlinker -framework,AppKit
NVCC_LIB = -Xlinker -rpath -Xlinker /Developer/NVIDIA/CUDA-5.5/lib
NVCC_ARCH = -Xcompiler -arch -Xcompiler x86_64
NVCC_STD = -Xcompiler -stdlib=libstdc++
NVCC_VCODE = -gencode arch=compute_10,code=sm_13 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=\"sm_35,compute_35\"
NVCC_FLAGS = -Xcompiler -Werror -Xcompiler -Wall -Xcompiler -Wextra

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(COBJ) #$(MLXLIB)
	$(NVCC) $(NVCC_C) $(NVCC_ARCH) $(NVCC_STD) $(NVCC_FRAMEWORK) $(NVCC_LIB) -o $(NAME) $(OBJ) $(LIBFT) $(COBJ) $(LIB)

$(LIBFT):
	make -C $(LIBFTDIR)

$(COBJ):
	$(NVCC) $(NVCC_C) $(NVCC_ARCH) $(NVCC_STD) $(NVCC_VCODE) $(NVCC_FLAGS) -I $(CUDA)/include -I header -I $(CUDAHDR) -c $(CSRC)

#$(MLXLIB):
#	make -C $(MLXDIR)

$(OBJ):
	gcc $(FLAGS) -iquote $(LIBFTDIR) -iquote $(CUDAHDR) -c $(SOURCE) $(LIB) -I libft/includes

clean:
	rm -f $(OBJ) $(COBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
