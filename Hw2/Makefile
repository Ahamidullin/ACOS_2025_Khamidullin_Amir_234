all: program libinterpose.dylib
# ---------- настройки ----------
CC      = clang
CFLAGS  = -Wall -g -fPIC
LIBM    = -lm

# ---------- статическая библиотека (fred+john) ----------
libstatic.a: fred.o john.o
	ar crv $@ $^

fred.o: fred.c
	$(CC) $(CFLAGS) -c $< -o $@
john.o: john.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBM)

# ---------- динамическая библиотека (bill+sam) ----------
libshared.dylib: bill.o sam.o
	$(CC) -shared -o $@ $^ $(LIBM)

bill.o: bill.c
	$(CC) $(CFLAGS) -c $< -o $@
sam.o: sam.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBM)

# ---------- библиотека‑перехватчик (load‑time) ----------
libinterpose.dylib: interpose_shared.o
	$(CC) -shared -o $@ $<

interpose_shared.o: interpose_shared.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------- объект‑перехватчик (link‑time) ----------
interpose_static.o: interpose_static.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------- основная программа ----------
program: program.o interpose_static.o libstatic.a libshared.dylib
	$(CC) -o $@ program.o interpose_static.o libstatic.a ./libshared.dylib $(LIBM)

program.o: program.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------- стандартные цели ----------

clean:
	rm -f *.o *.a *.dylib program
.PHONY: all clean
