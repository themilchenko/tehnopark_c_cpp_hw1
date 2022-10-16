build:
	cmake -B build
	make -C build

clean:
	rm -rf ./build

coverage: sanitizers_test
	lcov -c -d build/CMakeFiles/DZ1_Team.dir/source -o ./build/info
	genhtml ./build/info -o ./build/html

valgrind_test:
	cmake -B build
	make -C build
	cd build
	valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ctest -VV
	cd ..

sanitizers_test:
	cmake -B build -DSANITIZERS=ON
	make -C build all test

run:
	bash linters/run.sh