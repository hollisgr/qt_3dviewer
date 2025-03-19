CC := gcc 
CFLAGS := -Wall -Wextra -Werror -std=c11
LIBSFLAGS = -lcheck -lm -lsubunit
SOURCE_COMMON = common/*.c
COMMON = lib/s21_common.a
TEST_FILES = test_files/*.c
APP = build/opengl_cmake
DIST = 3D_Viewer_0_6969c
INC = common/*.h opengl_cmake/*.h test_files/*.h
SOURCE = common/*.c opengl_cmake/*.cpp test_files/*.c
CLANG = clang-format -style=Google
VALGRIND =  valgrind --tool=memcheck --leak-check=yes

all: install

install: uninstall
	mkdir build
	cd ./build/ && cmake ../opengl_cmake && make

clean: uninstall clean_common clean_report clean_test
	rm -rf *.tgz
	rm -rf opengl_cmake/build/
	rm -rf 3D_Viewer_0_6969c

clean_common:
	rm -rf lib

clean_test:
	rm -rf test

clean_report:
	rm -rf *.gcno *.gcda *.html *.css GCOVRreport lcov_report coverage.info

uninstall:
	rm -rf build

run:
	./$(APP)

$(COMMON): clean_common
	mkdir lib
	$(CC) $(CFLAGS) -c $(SOURCE_COMMON)
	ar r $(COMMON) *.o
	ranlib $(COMMON)
	rm -rf *.o

test: clean_test $(COMMON)
	$(CC) $(CFLAGS) -o test $(TEST_FILES) $(COMMON) $(LIBSFLAGS)
	./test

test_valg: clean_test $(COMMON)
	$(CC) $(CFLAGS) -o test $(TEST_FILES) $(COMMON) $(LIBSFLAGS)
	$(VALGRIND) ./test

gcov_report: clean_test clean_report $(COMMON)
	gcc -I inc --coverage $(SOURCE_COMMON) -o test ${TEST_FILES} $(COMMON) $(LIBSFLAGS)
	./test
	# ~/.local/bin/gcovr -r . --html-details -o gcov_report.html
	gcovr -r . --html-details -o gcov_report.html
	mkdir GCOVRreport
	mv *.html *.css GCOVRreport
	rm -rf *.gcno *.gcda

lcov_report: clean_test clean_report $(COMMON)
	gcc -I inc --coverage $(SOURCE_COMMON) -o test ${TEST_FILES} $(COMMON) $(LIBSFLAGS)
	./test
	lcov -t "Report" -c -d ./ --output-file ./coverage.info
	genhtml coverage.info --output-directory lcov_report/
	rm -rf *.gcno *.gcda

dvi:
	mkdir -p dvi
	texi2dvi readme.texi --dvi -o readme.dvi
	mv readme.* dvi
	mv dvi/readme.txt .
	mv dvi/readme.texi .

dist: clean
	mkdir $(DIST)/
	cp -a Makefile ./$(DIST)
	cp -a common ./$(DIST)
	cp -a opengl_cmake ./$(DIST)
	tar cvzf 3D_Viewer_0_6969c.tgz $(DIST)/
	rm -rf $(DIST)

checkformat:
	$(CLANG) -n $(INC)
	$(CLANG) -n $(SOURCE)

setformat:
	$(CLANG) -i $(INC)
	$(CLANG) -i $(SOURCE)
