all : NestedSwitchCommentCounter.exe StateTableCommentCounter.exe StatePatternCommentCounter.exe OptimalCommentCounter.exe

UnitTests : UnitTestNestedSwitch.exe UnitTestStateTable.exe UnitTestStatePattern.exe UnitTestOptimal.exe

### Nested switch code
NestedSwitchCommentCounter.exe: NestedSwitchCommentCounter.cpp TestCommentCounter.cpp
	g++ $^ -g -DNESTED_SWITCH -o $@

UnitTestNestedSwitch.exe: NestedSwitchCommentCounter.cpp UnitTestCommentCounter.cpp
	g++ $^ -g -DNESTED_SWITCH -DUNIT_TEST -o $@

### State Table code
StateTableCommentCounter.exe: StateTableCommentCounter.cpp TestCommentCounter.cpp
	g++ $^ -g -DSTATE_TABLE -o $@

UnitTestStateTable.exe: StateTableCommentCounter.cpp UnitTestCommentCounter.cpp
	g++ $^ -g -DSTATE_TABLE -DUNIT_TEST -o $@

### State Pattern Code
StatePatternCommentCounter.exe: StatePatternCommentCounter.cpp TestCommentCounter.cpp
	g++ $^ -g -DSTATE_PATTERN -o $@

UnitTestStatePattern.exe: StatePatternCommentCounter.cpp UnitTestCommentCounter.cpp
	g++ $^ -g -DSTATE_PATTERN -DUNIT_TEST -o $@

### Optimal Code
OptimalCommentCounter.exe: OptimalCommentCounter.cpp TestCommentCounter.cpp
	g++ $^ -g -o $@

UnitTestOptimal.exe: OptimalCommentCounter.cpp UnitTestCommentCounter.cpp
	g++ $^ -g -DUNIT_TEST -o $@
