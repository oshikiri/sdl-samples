all:
	clang-format *.cpp *.hpp -i
	em++ main.cpp \
		-Wall -Wextra -Wno-unused-parameter \
		-s USE_SDL=2 \
		-o index.html
