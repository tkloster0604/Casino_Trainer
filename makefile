PLATFORM ?= native
SRCS      = $(wildcard *.cpp)
WARNFLAGS = -Wall -Wextra -std=c++17 -MMD -MP

ifeq ($(PLATFORM),web)
    CXX      = em++
    BUILD    = build/web
    TARGET   = $(BUILD)/index.html
    CXXFLAGS = $(WARNFLAGS) -O2 -sUSE_GLFW=3
    LDFLAGS  = -sUSE_GLFW=3 \
               -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
               -sALLOW_MEMORY_GROWTH=1 \
               --preload-file assets
    LDLIBS   =
else
    CXX      = g++
    BUILD    = build/native
    TARGET   = casino
    CXXFLAGS = $(WARNFLAGS) -Ilibs/glad/include
    LDFLAGS  =
    LDLIBS   = -lglfw -lGL       # Windows/MinGW: -lglfw3 -lopengl32 -lgdi32
endif

OBJS = $(SRCS:%.cpp=$(BUILD)/%.o)
ifneq ($(PLATFORM),web)
    OBJS += $(BUILD)/glad.o
endif

DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/glad.o: libs/glad/src/glad.c | $(BUILD)
	$(CC) -O2 -Ilibs/glad/include -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

web:
	$(MAKE) PLATFORM=web all

serve: web
	python3 -m http.server 8080 -d build/web

clean:
	rm -rf build casino

-include $(DEPS)

.PHONY: all web serve clean