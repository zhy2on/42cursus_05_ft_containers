start=$(perl -MTime::HiRes=time -e 'printf "%.9f\n", time')

sleep 1

finish=$(perl -MTime::HiRes=time -e 'printf "%.9f\n", time')
diff=$( echo "$finish - $start" | bc -l )

printf "start: ${start}\n"
printf "finish: ${finish}\n"
printf "diff: %f\n" ${diff}
