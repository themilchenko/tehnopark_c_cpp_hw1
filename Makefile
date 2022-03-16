build:
	cmake -B build
	cd build
	make
	cd ..

clean:
	rm -rf ./build

test:
	cd build
	ctest -VV
	cd ..

run:
	zsh linters/run.sh

coverage:
	lcov -c -d build/CMakeFiles/DZ1_Team.dir/source -o ./build/info
	genhtml ./build/info -o ./build/html


