
NAME = humangl

FILES = main.cpp \
		Utilities.cpp \
		Shader.cpp \
		Object.cpp \
		RectangularCuboid.cpp \
		Human.cpp \
		Loop.cpp \
		World.cpp \
		Camera.cpp \
		Matrix.cpp \
		Vec3.cpp \
		bvhParser.cpp \
		AnimationHandler.cpp \
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
# -g flag for debug
CXXFLAGS = -std=gnu++14 -Wall -Wextra
#CXXFLAGS += -g #GNU
#CXXFLAGS += -fno-omit-frame-pointer #linux profiler
CXXFLAGS += -Wno-deprecated-declarations # hide usleep deprecated warning

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

obj/%.o:src/%.cpp includes/*.h $(wildacrd $(src/%.hpp))
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Iincludes -Ilibft

clean :
	rm -rf obj

fclean : clean
	rm -rf $(NAME)

re : fclean all

