
NAME = humangl

FILES = main.cpp \
		Utilities.cpp \
		Shader.cpp \
		Cube.cpp \
		Window.cpp

OBJ = $(addprefix obj/,$(FILES:.cpp=.o))

LIBS = -lglfw -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl `pkg-config --libs glew` -lm #linkage

UNAME = $(shell uname -s)
ifneq (, $(findstring MINGW, $(UNAME)))
	LIBS = -lglfw3 -lgdi32 -lglew32 -lopengl32
	NAME = humangl.exe
endif

CC = g++ --std=c++14 # 14 is fine for now, might need to upgrade ?

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

obj/%.o:src/%.cpp #includes/*.h #add rule here
	@mkdir -p obj
	$(CC) -g -Wall -Wextra -c $< -o $@ -Iincludes -Ilibft #added 'g' flag for debug

clean :
	rm -rf obj

fclean : clean
	rm -rf $(NAME)

re : fclean all

