
NAME = humangl

FILES = main.cpp \
		Utilities.cpp \
		Shader.cpp \
		Cube.cpp \
		Loop.cpp \
		Window.cpp

OBJ = $(addprefix obj/,$(FILES:.cpp=.o))

LIBS = -lglfw -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl `pkg-config --libs glew` -lm #linkage

UNAME = $(shell uname -s)
ifneq (, $(findstring MINGW, $(UNAME)))
	LIBS = -lglfw3 -lgdi32 -lglew32 -lopengl32
	NAME = humangl.exe
endif

CXXFLAGS = -g -std=gnu++14 -Wall -Wextra
CXXFLAGS += -Wno-deprecated-declarations # hide usleep deprecated warning

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

obj/%.o:src/%.cpp #includes/*.h #add rule here
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Iincludes -Ilibft

clean :
	rm -rf obj

fclean : clean
	rm -rf $(NAME)

re : fclean all

