cmd_/jason_with_LDD3/hello_modules/hello.ko := arm-linux-ld -EL -r  -T /Jason_with_ARM/linux-3.0.1/scripts/module-common.lds --build-id  -o /jason_with_LDD3/hello_modules/hello.ko /jason_with_LDD3/hello_modules/hello.o /jason_with_LDD3/hello_modules/hello.mod.o