make:
	g++ interpreter.cpp -Ilib-modules/ -o bin/jovon

run:
	./bin/jovon query.jnq

mr:
	g++ interpreter.cpp -Ilib-modules/ -o bin/jovon
	./bin/jovon query.jnq

cdmr:
	rm -rf test/*
	g++ interpreter.cpp -Ilib-modules/ -o bin/jovon
	./bin/jovon query.jnq

testc:
	rm -rf test/*

clean:
	rm bin/jovon
