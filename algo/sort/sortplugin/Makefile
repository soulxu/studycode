ALL: pop_sort.so insert_sort.so libsort.so plugin_test insert_binary_sort.so shell_sort.so stdc_qsort.so quick_sort.so select_sort.so select_heap_sort.so merge_sort.so radix_sort.so bucket_sort.so bst_sort.so

bst_sort.so: bst_sort.cpp
	$(CXX) -I../../tree/ -shared -o $@ $? $(CFLAGS)

bucket_sort.so: bucket_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

radix_sort.so: radix_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

merge_sort.so: merge_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

select_heap_sort.so: select_heap_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

select_sort.so: select_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

quick_sort.so: quick_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

stdc_qsort.so: stdc_qsort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

shell_sort.so: shell_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

pop_sort.so: pop_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

insert_sort.so: insert_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

insert_binary_sort.so: insert_binary_sort.c
	$(CC) -shared -o $@ $? $(CFLAGS)

libsort.so: sort.c sort.h
	$(CC) -shared -o $@ $? -ldl $(CFLAGS)

plugin_test: plugin_test.c
	$(CC) -o $@ $? -L. -lsort -ldl $(CFLAGS)

.PHONY: clean

clean:
	rm *.so plugin_test
