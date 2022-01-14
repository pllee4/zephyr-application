## Building process 
clean_build:
	rm -rf build
	mkdir -p build

app1:
	west build . -DAPP_NAME=app1