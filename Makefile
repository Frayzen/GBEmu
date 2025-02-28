all:
	@if [ ! -d build ]; then cmake . -B build; fi
	@make -C build all
clean:
	@rm -rf build
