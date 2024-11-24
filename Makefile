SANITIZER = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
DIFFERENT_FLAGS = -I include -D _DEBUG -lncurses -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla
OBJECTS = o_files/main.o o_files/reduceTree.o o_files/calcDiff.o o_files/latexDump.o o_files/readFile.o o_files/createTree.o o_files/delTree.o o_files/wrDotFile.o o_files/wrPngFile.o

all: init out

out: $(OBJECTS)
	g++ $(OBJECTS) -o out $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/main.o: source/main.cpp
	g++ -c source/main.cpp -o o_files/main.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/readFile.o: source/readFile/readFile.cpp
	g++ -c source/readFile/readFile.cpp -o o_files/readFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/createTree.o: source/mathTree/createTree.cpp
	g++ -c source/mathTree/createTree.cpp -o o_files/createTree.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/delTree.o: source/mathTree/delTree.cpp
	g++ -c source/mathTree/delTree.cpp -o o_files/delTree.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/wrDotFile.o: source/graphDump/wrDotFile.cpp
	g++ -c source/graphDump/wrDotFile.cpp -o o_files/wrDotFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/wrPngFile.o: source/graphDump/wrPngFile.cpp
	g++ -c source/graphDump/wrPngFile.cpp -o o_files/wrPngFile.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/latexDump.o: source/latexDump.cpp
	g++ -c source/latexDump.cpp -o o_files/latexDump.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/calcDiff.o: source/calcDiff.cpp
	g++ -c source/calcDiff.cpp -o o_files/calcDiff.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

o_files/reduceTree.o: source/mathTree/reduceTree.cpp
	g++ -c source/mathTree/reduceTree.cpp -o o_files/reduceTree.o $(DEBUG_SET)  $(DIFFERENT_FLAGS) $(SANITIZER)

clean:
	rm -rf o_files/*.o out o_files

init:
	mkdir -p o_files