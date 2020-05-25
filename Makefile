
NAME = humangl

FILES = main.cpp \
		Utilities.cpp \
		Shader.cpp \
		Cube.cpp \
		Loop.cpp \
		Matrix.cpp \
		Window.cpp

OBJ = $(addprefix obj/,$(FILES:.cpp=.o))

#linkage
LIBS = -lglfw -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl `pkg-config --libs glew` -lm

UNAME = $(shell uname -s)
ifneq (, $(findstring MINGW, $(UNAME)))
	LIBS = -lglfw3 -lgdi32 -lglew32 -lopengl32
	NAME = humangl.exe
endif

# 14 is fine for now, might need to upgrade ?
CC = g++ --std=c++14

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

obj/%.o:src/%.cpp #includes/*.h #add rule here
	@mkdir -p obj
#added 'g' flag for debug
	$(CC) -g -Wall -Wextra -c $< -o $@ -Iincludes -Ilibft

clean :
	rm -rf obj

fclean : clean
	rm -rf $(NAME)

re : fclean all

