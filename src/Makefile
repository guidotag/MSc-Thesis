CXX = g++
CXXFLAGS = -Wshadow -std=c++11 -O2 -DNDEBUG

SOLVERS_OBJS = main.o bounds.o backtracking.o dp.o utils.o mst.o vc.o approximation.o
GENERATOR_OBJS = generator.o
BOUNDS_TIMER_OBJS = bounds_timer.o bounds.o utils.o mst.o vc.o
SOLVERS_TIMER_OBJS = solvers_timer.o bounds.o backtracking.o dp.o utils.o mst.o vc.o approximation.o

.PHONY: all dirs clean solvers bounds_timer solvers_timer generator

all: dirs solvers generator bounds_timer solvers_timer

dirs:
	mkdir -p instance
	mkdir -p data/bounds
	mkdir -p data/solvers
	mkdir -p plot/bounds_epslatex
	mkdir -p plot/bounds_png

approximation.o: approximation.cpp approximation.h defines.h utils.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

backtracking.o: backtracking.cpp defines.h bounds.h utils.h approximation.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

bounds.o: bounds.cpp bounds.h utils.h mst.h vc.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

bounds_timer.o: bounds_timer.cpp bounds.h defines.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

solvers_timer.o: solvers_timer.cpp backtracking.h dp.h defines.h
	$(CXX) $(CXXFLAGS) $< -c -o $@ 

dp.o: dp.cpp defines.h utils.h bounds.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

generator.o: generator.cpp defines.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

main.o: main.cpp defines.h dp.h backtracking.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

mst.o: mst.cpp mst.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

vc.o: vc.cpp vc.h network.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

utils.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

solvers: $(SOLVERS_OBJS)
	$(CXX) $^ -o $@

bounds_timer: $(BOUNDS_TIMER_OBJS)
	$(CXX) $^ -o $@

solvers_timer: $(SOLVERS_TIMER_OBJS)
	$(CXX) $^ -o $@

generator: $(GENERATOR_OBJS)
	$(CXX) $^ -o $@

clean:
	rm -rf $(SOLVERS_OBJS) $(BOUNDS_TIMER_OBJS) $(SOLVERS_TIMER_OBJS) $(GENERATOR_OBJS)
	rm -rf solvers
	rm -rf generator
	rm -rf bounds_timer
	rm -rf solvers_timer