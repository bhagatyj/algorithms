include Makefile.def

archive: obj/liblutils.a

OBJS := obj/sll.o

obj/liblutils.a: $(OBJS)
	$(LIBLD) $(LIBLDFLAGS) obj/liblutils.a $(OBJS)


# pull in the dependency info for existing .o files
-include $(OBJS: .o=.d)

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) src/$*.c -o obj/$*.o
	$(CC) -MM $(CFLAGS) src/$*.c > obj/$*.d

clean:
	rm -f obj/*
