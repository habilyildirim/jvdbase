make:
	g++ interpreter.cpp -Ilib-modules/ -o bin/jovon

run:
	sudo ./bin/jovon query.jnq

clean:
	rm bin/jovon
	rm -rf test/*
	rm query.jnq
	touch query.jnq
