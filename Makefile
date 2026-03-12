
NB_PROCS=8

debug:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_C_COMPILER_LAUNCHER=ccache \
		-DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
		-S ../.. \
		-B . \
	&& \
	make -j ${NB_PROCS}

debugWithTests:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DENABLE_TESTS=ON \
		-DCMAKE_C_COMPILER_LAUNCHER=ccache \
		-DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
		-S ../.. \
		-B . \
	&& \
	make -j ${NB_PROCS}

release:
	mkdir -p cmake-build/Release && \
	cd cmake-build/Release && \
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_C_COMPILER_LAUNCHER=ccache \
		-DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
		-S ../.. \
		-B . \
	&& \
	make -j ${NB_PROCS}

clean:
	rm -rf cmake-build

cleanSandbox:
	rm -rf sandbox

# https://unix.stackexchange.com/questions/116389/recursively-delete-all-files-with-a-given-extension
cleanCoverage:
	find . -type f -name '*.gcda' -delete

copyData:
	mkdir -p sandbox/
	rsync -avH assets sandbox/
	rsync -avH scripts/ sandbox/

copyDebug: debug copyData
	rsync -avH cmake-build/Debug/lib cmake-build/Debug/bin sandbox/

copyRelease: release copyData
	rsync -avH cmake-build/Release/lib cmake-build/Release/bin sandbox/

run: copyRelease
	cd sandbox && ./run.sh pge_app

drun: copyDebug
	cd sandbox && ./debug.sh pge_app

# https://stackoverflow.com/questions/3931741/why-does-make-think-the-target-is-up-to-date
PHONY: .tests
tests: debugWithTests copyDebug

# https://stackoverflow.com/questions/2826029/passing-additional-variables-from-command-line-to-make
# Use like this:
# make rununittests test_filters="Unit_Pge_App_Controls*"
# make rununittests test_filters="Unit_Pge_App_Controls*" test_repeat=10
rununittests: tests cleanCoverage
	cd sandbox && ./tests.sh unitTests $(test_filters) $(test_repeat)

runintegrationtests: tests cleanCoverage
	cd sandbox && ./tests.sh integrationTests $(test_filters) $(test_repeat)

profile: copyDebug
	cd sandbox && ./profile.sh pge_app

# https://stackoverflow.com/questions/28896909/how-to-call-clang-format-over-a-cpp-project-folder
format:
	find src/ -iname '*.hh' -o -iname '*.cpp' | xargs clang-format -i
	find tests/ -iname '*.hh' -o -iname '*.cpp' | xargs clang-format -i
