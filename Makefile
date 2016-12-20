main:
	gcc achtung_c.c achtung_gtk.c key_events.c backgroundInit.c main.c -lm -o achtung `pkg-config --cflags --libs gtk+-3.0` 