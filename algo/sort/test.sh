#!/bin/bash
i=0
while [ $i -lt 10000000 ];
do
	i=`expr $i + 50000`
	./sort ./data.txt $i ./out.txt "quick sort"
done


