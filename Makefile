## Building process 
clean_build:
	rm -rf build
	mkdir -p build

app1:
	west build -d build/app1 -- -DAPP_NAME=app1