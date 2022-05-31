all:
	clang-format main.c sdl_extra.h -i
	emcc main.c \
		-s USE_SDL=2 \
		--preload-file font -s USE_SDL_TTF=2 \
		-o index.html
