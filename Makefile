# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/03 17:50:09 by aalliot           #+#    #+#              #
#    Updated: 2015/02/03 19:39:58 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol

HDRDIR	= header
SRCDIR	= src
OBJDIR	= obj
CUDASRC	= cudasrc
CUDAHDR	= cudaheader
CUDAOBJ	= cudaobj
LIBHDR	= libft/includes
LIBDIR	= libft/
LIBFT	= $(LIBDIR)libft.a

SRC		=	main.c			\
			color.c			\
			cpu_frac.c		\
			gpu_frac.c		\
			hook.c			\
			init.c			\
			lib2d.c

CSRC	=	mandelbrot.cu	\
			julia.cu		\
			douady.cu

OBJ		=	$(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
SCUDA	=	$(patsubst %.cu,$(CUDAOBJ)/%.o,$(CSRC))

NORMINETTE	= ~/project/colorminette/colorminette

FLAGS	= -Wall -Werror -Wextra -iquote header -framework OpenGL -framework AppKit
LIB				= -L/usr/X11/lib -lmlx -lXext -lX11 -I /opt/X11/include/
CUDA			= /Developer/NVIDIA/CUDA-5.5
NVCC			= /Developer/NVIDIA/CUDA-5.5/bin/nvcc
NVCC_C			= -ccbin /usr/bin/clang -m64 -Xcompiler -arch -Xcompiler x86_64 -Xcompiler -stdlib=libstdc++
NVCC_FRAMEWORK	= -Xlinker -framework,OpenGL -Xlinker -framework,AppKit
NVCC_LIB		= -Xlinker -rpath -Xlinker /Developer/NVIDIA/CUDA-5.5/lib
NVCC_VCODE		= -gencode arch=compute_13,code=sm_13 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=\"sm_35,compute_35\"
NVCC_FLAGS		= -Xcompiler -Werror -Xcompiler -Wall -Xcompiler -Wextra

$(shell mkdir -p $(OBJDIR) $(CUDAOBJ))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(SCUDA)
	$(NVCC) -O4 $(NVCC_C) $(NVCC_FRAMEWORK) $(NVCC_LIB) -o $(NAME) $(OBJ) $(LIBFT) $(SCUDA) $(LIB)

$(LIBFT):
	make -C $(LIBDIR)

$(CUDAOBJ)/%.o: $(CUDASRC)/%.cu
	$(NVCC) -O4 $(NVCC_C) $(NVCC_VCODE) $(NVCC_FLAGS) -I $(CUDA)/include -I header -I $(CUDAHDR) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc -O4 $(FLAGS) $(LIB) -I libft/includes -iquote $(LIBDIR) -iquote $(CUDAHDR) -o $@ -c $<

.PHONY: clean fclean re norme

norme:
	@make -C libft/ norme
	@$(NORMINETTE) $(SRCDIR)/ $(HDRDIR)/

clean:
	rm -f $(OBJ) $(SCUDA)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean
	make
