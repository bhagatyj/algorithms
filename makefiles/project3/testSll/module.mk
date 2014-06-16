SRC += testSll/sllTest.y
LIBS += -ly
%.c %.h: %.y
	$(YACC) -d $*.y
	mv y.tab.c $*.c
	mv y.tab.h $*.h
