
NB_PROCS=8

debug:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		../.. \
	&& \
	make -j ${NB_PROCS}

debugWithTests:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DENABLE_TESTS=ON \
		../.. \
	&& \
	make -j ${NB_PROCS}

release:
	mkdir -p cmake-build/Release && \
	cd cmake-build/Release && \
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		../.. \
	&& \
	make -j ${NB_PROCS}

clean:
	rm -rf cmake-build

cleanSandbox:
	rm -rf sandbox

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

rununittests: tests
	cd sandbox && ./tests.sh unitTests

runintegrationtests: tests
	cd sandbox && ./tests.sh integrationTests

profile: copyDebug
	cd sandbox && ./profile.sh pge_app
