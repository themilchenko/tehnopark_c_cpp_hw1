build:
	cmake -B build
	make -C build

clean:
	rm -rf ./build

coverage: test
	lcov -c -d build/CMakeFiles/DZ1_Team.dir/source -o ./build/info
	genhtml ./build/info -o ./build/html

test:
	cmake -B build
	make -C build
	cd build/tests
	valgrind ./test_team
	cd ../..

run:
	bash linters/run.sh