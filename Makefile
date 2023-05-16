# -=-=-=-=-	NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
NAME    	:= fdf
BNUS_NAME	:= fdf_bonus
MKFL		:= Makefile
# -=-=-=-=-	CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
DEF_CLR		:= \033[0;39m
GRAY		:= \033[0;90m
RED			:= \033[0;91m
GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
MAGENTA		:= \033[0;95m
CYAN		:= \033[0;96m
WHITE		:= \033[0;97m
# -=-=-=-=-	PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
INC_DIR	:= inc/
SRC_DIR	:= src/
##TUL_DIR	:= tools/
#UTL_DIR	:= utils/
OBJ_DIR	:= .objs/
DEP_DIR	:= .deps/
LIBS	= ./libraries/
LIB_DIR	= $(LIBS)clift/
LFT_DIR	= $(LIB_DIR)libft/
OUT_DIR	= $(LIB_DIR)liboutput/
MLX_DIR	= minilibx_macos/

# -=-=-=-=-	CMND -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
#UNAME		= $(shell uname)
CFLAGS		= -Wall -Wextra -Werror -W
#XFLAGS		= -fsanitize=address -g
DFLAGS		= -MT $@ -MMD -MP
LFLAGS		= -lm
FRAMEWORK	= -framework OpenGL -framework AppKit
LNX_MLX		= -ldl -lglfw3 -pthread -lm
AR		= ar -rcs
RM		= rm -f
MK		= mkdir -p
CP		= cp -f
# -=-=-=-=-	FILE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
LIBRARY	= $(LIB_DIR)libft.a #$(LIB_DIR)liboutput.a
MLX_LIB	= $(MLX_DIR)libmlx.a
INCLUDE	= -I$(INC_DIR) -I$(MLX_DIR) \
		-I$(LIB_DIR)-I$(OUT_DIR)$(INC_DIR)
FDF_SRC	=  mlx_init.c
##FDF_TUL	= 
#FDF_UTL	= 
SRCS	+= $(addprefix $(SRC_DIR), $(FDF_SRC))
#SRCS	+= $(addprefix $(TUL_DIR), $(FDF_TUL))
#SRCS	+= $(addprefix $(UTL_DIR), $(FDF_UTL))
OBJS	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS	= $(addprefix $(DEP_DIR), $(addsuffix .d, $(basename $(SRCS))))
FT_LINK = -L$(LIB_DIR) -lft
# -=-=-=-=-	RULE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
$(OBJ_DIR)%.o: %.c $(MKFL)
	@$(MK) $(dir $@) $(dir $(subst $(OBJ_DIR), $(DEP_DIR), $@))
	@printf "\r$(GREEN)\tCompiling: $(YELLOW)$< $(DEF_CLR)                   \r"
	@$(CC) $(CFLAGS) $(DFLAGS)  $(INCLUDE) -c $< -o $@
	@mv $(patsubst %.o, %.d, $@) $(dir $(subst $(OBJ_DIR), $(DEP_DIR), $@))
all:
	@$(MAKE) -sC $(MLX_DIR)
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) $(NAME)
run:
	@$(MAKE) -sC $(MLX_DIR)
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) $(NAME)
	@./$(NAME) tests/cpeset-c.fdf
$(NAME):: $(OBJS)
	@$(CC) $(CFLAGS) $(XFLAGS) $(FRAMEWORK) $(OBJS) $(LIBRARY) $(MLX_LIB) $(FT_LINK) $(LFLAGS) -o $(NAME);
	@printf "\n\t$(WHITE)Program \033[1;31mFDF $(WHITE)has been compiled!$(DEF_COLOR)\n"
$(NAME)::
	@printf "\t$(WHITE)Nothing more to be done for program \033[1;31mFDF$(DEF_COLOR)\n"
-include $(DEPS)
clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@echo "$(BLUE)	FDF object and dependencies files cleaned.$(DEF_COLOR)"
fclean:
	@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@$(RM) $(NAME)
	@echo "$(WHITE)	All objects, dependencies and executables removed.$(DEF_COLOR)"
re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(GREEN)	Cleaned and rebuilt everything for fdf project.$(DEF_COLOR)"
norm:
	@norminette $(INC_DIR) $(SRC_DIR) $(TUL_DIR) $(UTL_DIR) $(LIB_DIR)
.PHONY: all clean fclean re norm









