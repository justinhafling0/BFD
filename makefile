
all: clean libobjdata.a libobjdata.so getsections getsyms gettxt getsections_dl getsyms_dl

libobjdata.a:
	gcc -c -o objcopy.o objcopy.c
	gcc -c -o objsyms.o objsyms.c
	gcc -c -o objsects.o objsects.c
	ar rs $@ objsects.o objsyms.o objcopy.o

libobjdata.so:
	gcc -c -fPIC -o objsyms.pic.o objsyms.c
	gcc -c -fPIC -o objsects.pic.o objsects.c
	gcc -c -fPIC -o objcopy.pic.o objcopy.c
	gcc -shared -o libobjdata.so objsyms.pic.o objsects.pic.o -lbfd



getsections:
	gcc -o getsections getsections.c libobjdata.a -lbfd

getsyms:
	gcc -o getsyms getsyms.c libobjdata.a -lbfd

gettxt:
	gcc -o gettxt gettxt.c libobjdata.a -lbfd





getsections_dl:
	gcc -I./ -L./ -o getsections_dl getsections_dl.c -ldl -lbfd -lobjdata

getsyms_dl:
	gcc -I./ -L./ -o getsyms_dl getsyms_dl.c -ldl -lbfd -lobjdata

getsyms_dl:

	gcc -I./ -L./ -o getsyms_dl getsyms_dl.c -lobjdata -ldl



clean:
	rm -f *.o *.so *.a objsects objsyms getsections getsyms getsections_dl getsyms_dl text-output